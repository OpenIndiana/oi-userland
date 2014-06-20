# vim: tabstop=4 shiftwidth=4 softtabstop=4

# Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
#
#    Licensed under the Apache License, Version 2.0 (the "License"); you may
#    not use this file except in compliance with the License. You may obtain
#    a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
#    WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
#    License for the specific language governing permissions and limitations
#    under the License.
#
# @author: Girish Moodalbail, Oracle, Inc.

import netaddr
import rad.client as radcli
import rad.connect as radcon
import rad.bindings.com.oracle.solaris.rad.evscntl_1 as evsbind

from oslo.config import cfg

from neutron.api.rpc.agentnotifiers import dhcp_rpc_agent_api
from neutron.api.rpc.agentnotifiers import l3_rpc_agent_api
from neutron.api.v2 import attributes
from neutron.common import constants as l3_constants
from neutron.common import exceptions
from neutron.common import rpc as q_rpc
from neutron.common import topics
from neutron.db import db_base_plugin_v2
from neutron.db import dhcp_rpc_base
from neutron.db import external_net_db
from neutron.db import l3_rpc_base
from neutron.extensions import external_net
from neutron.extensions import providernet
from neutron.openstack.common import lockutils
from neutron.openstack.common import log as logging
from neutron.openstack.common import rpc
from neutron.plugins.common import constants as svc_constants
from neutron.plugins.evs.db import api as evs_db
from neutron.plugins.evs.db import l3nat as evs_l3nat
from neutron.plugins.evs.db import quotas_db


LOG = logging.getLogger(__name__)

evs_controller_opts = [
    cfg.StrOpt('evs_controller', default='ssh://evsuser@localhost',
               help=_("An URI that specifies an EVS controller"))
]

evs_database_opts = [
    cfg.StrOpt('sql_connection',
               default='sqlite:////var/lib/neutron/neutron.sqlite',
               help=_("An URI that specifies SQL connectionr")),
]

cfg.CONF.register_opts(evs_controller_opts, "EVS")
cfg.CONF.register_opts(evs_database_opts, "DATABASE")

# Maps OpenStack network resource attributes to EVS properties
NETWORK_EVS_ATTRIBUTE_MAP = {
    'tenant_id': 'tenant',
    'network_id': 'evs',
    'id': 'evs',
    'name': 'evs',
    external_net.EXTERNAL: 'OpenStack:' + external_net.EXTERNAL,
}

# Maps OpenStack subnet resource attributes to EVS' IPnet properties
SUBNET_IPNET_ATTRIBUTE_MAP = {
    'tenant_id': 'tenant',
    'network_id': 'evs',
    'id': 'ipnet',
    'name': 'ipnet',
    'enable_dhcp': 'OpenStack:enable_dhcp',
    'dns_nameservers': 'OpenStack:dns_nameservers',
    'host_routes': 'OpenStack:host_routes',
}

# Maps OpenStack port resource attributes to EVS' VPort properties
PORT_VPORT_ATTRIBUTE_MAP = {
    'tenant_id': 'tenant',
    'network_id': 'evs',
    'id': 'vport',
    'name': 'vport',
    'device_id': 'OpenStack:device_id',
    'device_owner': 'OpenStack:device_owner',
}


class EVSControllerError(exceptions.NeutronException):
    message = _("EVS controller: %(errmsg)s")

    def __init__(self, evs_errmsg):
        super(EVSControllerError, self).__init__(errmsg=evs_errmsg)


class EVSOpNotSupported(exceptions.NeutronException):
    message = _("Operation not supported by EVS plugin: %(opname)s")

    def __init__(self, evs_errmsg):
        super(EVSOpNotSupported, self).__init__(opname=evs_errmsg)


class EVSRpcCallbacks(dhcp_rpc_base.DhcpRpcCallbackMixin,
                      l3_rpc_base.L3RpcCallbackMixin):
    RPC_API_VERSION = '1.1'

    def create_rpc_dispatcher(self):
        '''Get the rpc dispatcher for this manager.

        If a manager would like to set an rpc API version, or support more than
        one class as the target of rpc messages, override this method.
        '''
        return q_rpc.PluginRpcDispatcher([self])


class EVSNeutronPluginV2(db_base_plugin_v2.NeutronDbPluginV2,
                         external_net_db.External_net_db_mixin,
                         evs_l3nat.EVS_L3_NAT_db_mixin):
    """Implements v2 Neutron Plug-in API specification.

    All the neutron API calls to create/delete/retrieve Network/Subnet/Port
    are forwarded to EVS controller through Solaris RAD. The RAD connection
    to EVS Controller is over SSH. In order that this plugin can communicate
    with EVS Controller non-interactively and securely, one should setup SSH
    authentication with pre-shared keys between the host running neutron-server
    and the host running EVS controller.

    The following table maps OpenStack Neutron resources and attributes to
    Solaris Elastic Virtual Switch resources and attributes

    |---------------------+------------------+------------------------------|
    | OpenStack Neutron   | Solaris EVS      | Comments                     |
    |---------------------+------------------+------------------------------|
    | Network             | EVS              | Represents an isolated L2    |
    | -- name             | -- name          | segment; implemented either  |
    | -- id               | -- uuid          | through VLANs or VXLANs      |
    | -- tenant_id        | -- tenant        |                              |
    | -- shared           | Always False     |                              |
    | -- admin_state_up   | Always True      |                              |
    | -- status           | Always ACTIVE    |                              |
    | -- provider:        |                  |                              |
    |    network_type     |  -- l2-type      | (either VLAN or VXLAN)       |
    | -- provider:        |                  |                              |
    |    segmentation_id  |  -- vlanid/vni   |                              |
    |                     |                  |                              |
    |                     |                  |                              |
    | Subnet              | IPnet            | An IP network represents     |
    | -- name             | -- name          | a block of either IPv4       |
    | -- id               | -- uuid          | or IPv6 addresses (subnet)   |
    | -- network_id       | -- evs           | along with a default router  |
    | -- tenant_id        | -- tenant        | for the block                |
    | -- cidr             | -- subnet        |                              |
    | -- gateway_ip       | -- defrouter     |                              |
    | -- allocation_pools | -- start/stop    |                              |
    | -- dns_nameservers  | -- OpenStack:\   |                              |
    |                     | dns_nameservers  |                              |
    | -- host_routes      | -- OpenStack:\   |                              |
    |                     | host_routes      |                              |
    | -- enable_dhcp      | -- OpenStack:\   |                              |
    |                     | enable_dhcp      |                              |
    | -- shared           | Always False     |                              |
    |                     |                  |                              |
    | Port                | VPort            | A VPort represents the point |
    | -- name             | -- name          | of attachment between the    |
    | -- id               | -- uuid          | VNIC and an EVS. It          |
    | -- network_id       | -- evs           | encapsulates various network |
    | -- tenant_id        | -- tenant        | configuration parameters (   |
    | -- status           | -- status        | MAC addresses, IP addresses, |
    | -- mac_address      | -- macaddr       | and SLAs)                    |
    | -- fixed_ips        | -- ipaddr        |                              |
    | -- device_id        | -- OpenStack:\   |                              |
    |                     |    device_id     |                              |
    | -- device_owner     | -- OpenStack:\   |                              |
    |                     |    device_owner  |                              |
    | -- security_groups  | -- Not Supported |                              |
    | -- admin_state_up   | Always UP        |                              |
    |---------------------+------------------+------------------------------|
    """

    # These attribute specifies whether the plugin supports or not
    # bulk/pagination/sorting operations.
    __native_bulk_support = False
    __native_pagination_support = False
    __native_sorting_support = False

    _supported_extension_aliases = ["provider", "external-net", "router",
                                    "quotas"]

    def __init__(self):
        # Since EVS Framework does not support router and floatingip
        # resources, the plugin itself will maintain a DB for these
        # two resources
        evs_db.configure_db()

        # Since there is no connect_uri() yet, we need to do this ourselves
        # parse ssh://user@hostname
        suh = cfg.CONF.EVS.evs_controller.split('://')
        if len(suh) != 2 or suh[0] != 'ssh' or not suh[1].strip():
            raise SystemExit(_("Specified evs_controller is invalid"))
        uh = suh[1].split('@')
        if len(uh) != 2 or not uh[0].strip() or not uh[1].strip():
            raise SystemExit(_("'user' and 'hostname' need to be specified "
                               "for evs_controller"))

        # TODO(gmoodalb): - try few times before you give up
        self._rc = radcon.connect_ssh(uh[1], user=uh[0])
        self._evsc = self._rc.get_object(evsbind.EVSController())
        self._setup_rpc()

    def _setup_rpc(self):
        # RPC support
        self.service_topics = {svc_constants.CORE: topics.PLUGIN,
                               svc_constants.L3_ROUTER_NAT: topics.L3PLUGIN}
        self.conn = rpc.create_connection(new=True)
        self.callbacks = EVSRpcCallbacks()
        self.dispatcher = self.callbacks.create_rpc_dispatcher()
        for svc_topic in self.service_topics.values():
            self.conn.create_consumer(svc_topic, self.dispatcher, fanout=False)
        # Consume from all consumers in a thread
        self.conn.consume_in_thread()
        self.dhcp_agent_notifier = dhcp_rpc_agent_api.DhcpAgentNotifyAPI()

    @property
    def supported_extension_aliases(self):
        return self._supported_extension_aliases

    def _convert_evs_to_network(self, evs):
        """Converts an EVS structure into Neutron Network structure."""

        networkdict = dict()
        networkdict['name'] = evs.name
        networkdict['id'] = evs.uuid
        networkdict['subnets'] = ([ipnet.uuid for ipnet in evs.ipnets]
                                  if evs.ipnets else [])
        networkdict['tenant_id'] = evs.tenantname
        networkdict[external_net.EXTERNAL] = False
        for prop in evs.props:
            if prop.name == 'l2-type':
                networkdict[providernet.NETWORK_TYPE] = prop.value
            if prop.name == 'vlanid' or prop.name == 'vni':
                networkdict[providernet.SEGMENTATION_ID] = int(prop.value)
            if prop.name == NETWORK_EVS_ATTRIBUTE_MAP[external_net.EXTERNAL]:
                networkdict[external_net.EXTERNAL] = \
                    (True if prop.value == 'True' else False)
        # fixed values as EVS framework doesn't support this
        networkdict['admin_state_up'] = True
        networkdict['status'] = 'ACTIVE'
        networkdict['shared'] = False

        return networkdict

    def _convert_ipnet_to_subnet(self, ipnet):
        """Converts an EVS IPnet structure into Neutron Subnet structure."""

        subnetdict = dict()
        subnetdict['name'] = ipnet.name
        subnetdict['network_id'] = ipnet.evsuuid
        subnetdict['id'] = ipnet.uuid
        subnetdict['tenant_id'] = ipnet.tenantname
        subnetdict['ip_version'] = \
            (4 if ipnet.ipvers == evsbind.IPVersion.IPV4 else 6)
        # assign default values to some subnet attributes
        subnetdict['dns_nameservers'] = []
        subnetdict['host_routes'] = []
        subnetdict['enable_dhcp'] = False
        for prop in ipnet.props:
            if prop.name == 'defrouter':
                subnetdict['gateway_ip'] = prop.value
            if prop.name == 'subnet':
                subnetdict['cidr'] = prop.value
            if prop.name == SUBNET_IPNET_ATTRIBUTE_MAP['enable_dhcp']:
                subnetdict['enable_dhcp'] = \
                    (True if prop.value == 'True' else False)
            if prop.name == SUBNET_IPNET_ATTRIBUTE_MAP['dns_nameservers']:
                subnetdict['dns_nameservers'] = prop.value.split(',')
            if prop.name == SUBNET_IPNET_ATTRIBUTE_MAP['host_routes']:
                hrlist = []
                vlist = prop.value.split(',')
                for i in range(0, len(vlist), 2):
                    hrlist.append({vlist[i]: vlist[i + 1]})
                subnetdict['host_routes'] = hrlist
        # EVS Controller returns a pool that includes gateway_ip as-well,
        # however neutron expects pool without gateway_ip. So, we determine
        # the pool ourselves here.
        assert 'gateway_ip' in subnetdict
        start_ip = netaddr.IPAddress(ipnet.start)
        end_ip = netaddr.IPAddress(ipnet.end)
        gw_ip = netaddr.IPAddress(subnetdict['gateway_ip'])
        pools = []
        if gw_ip == start_ip:
            pools.append({'start': str(netaddr.IPAddress(start_ip + 1)),
                          'end': str(netaddr.IPAddress(end_ip))})
        elif gw_ip == end_ip:
            pools.append({'start': str(netaddr.IPAddress(start_ip)),
                          'end': str(netaddr.IPAddress(end_ip - 1))})
        else:
            pools.append({'start': str(netaddr.IPAddress(start_ip)),
                          'end': str(netaddr.IPAddress(gw_ip - 1))})
            pools.append({'start': str(netaddr.IPAddress(gw_ip + 1)),
                          'end': str(netaddr.IPAddress(end_ip))})

        subnetdict['allocation_pools'] = pools
        subnetdict['shared'] = False

        return subnetdict

    def _convert_vport_to_port(self, context, vport):
        """Converts an EVS VPort structure into Neutron port structure."""

        portdict = dict()
        portdict['admin_state_up'] = True
        portdict['id'] = vport.uuid
        portdict['name'] = vport.name
        portdict['network_id'] = vport.evsuuid
        # TODO(gmoodalb): set to host/zonename/vnicname?
        portdict['device_id'] = ''
        portdict['device_owner'] = ''
        for prop in vport.props:
            if (prop.name == 'macaddr'):
                portdict['mac_address'] = prop.value
            if (prop.name == 'ipaddr'):
                evs = self.get_network(context, vport.evsuuid)
                portdict['fixed_ips'] = \
                    [{
                        'ip_address': prop.value.split('/')[0],
                        'subnet_id': evs['subnets'][0],
                    }]
            if (prop.name == 'OpenStack:device_id'):
                portdict['device_id'] = prop.value
            if (prop.name == 'OpenStack:device_owner'):
                portdict['device_owner'] = prop.value
        portdict['security_groups'] = []
        portdict['status'] = 'ACTIVE'
        portdict['tenant_id'] = vport.tenantname

        return portdict

    def _apply_rsrc_props_filter(self, rsrclist, filters):
        # if all of the filter values are None, then return
        if all([value is None for value in filters.values()]):
            return

        rsrc_to_remove = []
        for rsrc in rsrclist:
            propdict = dict((prop.name, prop.value) for prop in rsrc.props)
            for key, value in filters.iteritems():
                if value is None:
                    continue
                if key not in propdict:
                    rsrc_to_remove.append(rsrc)
                    break
                elif isinstance(value, list):
                    strlist = [str(v) for v in value]
                    if propdict[key] not in strlist:
                        rsrc_to_remove.append(rsrc)
                        break
                # TODO(gmoodalb): - check if it's an instance of basestring?
                elif propdict[key] != str(value):
                    rsrc_to_remove.append(rsrc)
                    break

        for rsrc in rsrc_to_remove:
            rsrclist.remove(rsrc)

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def evs_controller_addIPnet(self, tenantname, evsname, ipnetname, propstr):
        try:
            pat = radcli.ADRGlobPattern(
                {'name': evsname, 'tenant': tenantname})
            evs = self._rc.get_object(evsbind.EVS(), pat)
            ipnet = evs.addIPnet(propstr, ipnetname)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)
        return ipnet

    def create_subnet(self, context, subnet):
        """Creates a subnet(IPnet) for a given network(EVS).

         An IP network represents a block of either IPv4 or IPv6 addresses
         (i.e., subnet) along with a default router for the block. Only one
         IPnet can be associated with an EVS. All the zones/VNICs that
         connect to the EVS, through a VPort, will get an IP address from the
         IPnet associated with the EVS.
        """
        if (subnet['subnet']['allocation_pools'] is not
                attributes.ATTR_NOT_SPECIFIED):
            # user specified --allocation-pool and we don't support it
            raise EVSOpNotSupported(_("cannot use --allocation-pool"))
        ipnetname = subnet['subnet']['name']
        if not ipnetname:
            ipnetname = None

        proplist = ['subnet=%s' % (subnet['subnet']['cidr'])]

        # obtain the optional default router
        defrouter = subnet['subnet']['gateway_ip']
        if defrouter is None:
            # user specified --no-gateway and we don't support it
            raise EVSOpNotSupported(_("cannot use --no-gateway"))

        if defrouter is not attributes.ATTR_NOT_SPECIFIED:
            proplist.append('defrouter=%s' % (defrouter))

        # obtain the optional DNS nameservers
        nameservers = subnet['subnet']['dns_nameservers']
        if attributes.is_attr_set(nameservers):
            proplist.append('%s=%s' %
                            (SUBNET_IPNET_ATTRIBUTE_MAP['dns_nameservers'],
                             ','.join(nameservers)))

        # obtain the host routes
        hostroutes = subnet['subnet']['host_routes']
        if attributes.is_attr_set(hostroutes):
            hrlist = ['%s,%s' % (destination, nexthop)
                      for destination, nexthop in hostroutes]
            proplist.append('%s=%s' %
                            (SUBNET_IPNET_ATTRIBUTE_MAP['host_routes'],
                             ",".join(hrlist)))

        enable_dhcp = subnet['subnet']['enable_dhcp']
        proplist.append('%s=%s' %
                        (SUBNET_IPNET_ATTRIBUTE_MAP['enable_dhcp'],
                         enable_dhcp))

        propstr = None
        if proplist:
            propstr = ",".join(proplist)

        evsname = subnet['subnet']['network_id']
        tenantname = self._get_tenant_id_for_create(context, subnet['subnet'])
        ipnet = self.evs_controller_addIPnet(tenantname, evsname, ipnetname,
                                             propstr)
        retval = self._convert_ipnet_to_subnet(ipnet)

        # notify dhcp agent of subnet creation
        self.dhcp_agent_notifier.notify(context, {'subnet': retval},
                                        'subnet.create.end')
        return retval

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def evs_controller_updateIPnet(self, ipnetuuid, propstr):
        try:
            pat = radcli.ADRGlobPattern({'uuid': ipnetuuid})
            ipnetlist = self._rc.list_objects(evsbind.IPnet(), pat)
            assert len(ipnetlist) == 1
            ipnet = self._rc.get_object(ipnetlist[0])
            ipnet.setProperty(propstr)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)

    def update_subnet(self, context, id, subnet):
        evs_rpccall_sync = subnet.pop('evs_rpccall_sync', False)
        if not (set(subnet['subnet'].keys()) == set(('enable_dhcp',))):
                raise EVSOpNotSupported(_("only subnets with enable_dhcp "
                                          "set can be updated"))

        propstr = "%s=%s" % (SUBNET_IPNET_ATTRIBUTE_MAP['enable_dhcp'],
                             subnet['subnet']['enable_dhcp'])
        self.evs_controller_updateIPnet(id, propstr)
        retval = self.get_subnet(context, id)

        # notify dhcp agent of subnet update
        methodname = 'subnet.update.end'
        payload = {'subnet': retval}
        if not evs_rpccall_sync:
            self.dhcp_agent_notifier.notify(context, payload, methodname)
        else:
            msg = self.dhcp_agent_notifier.make_msg(
                methodname.replace(".", "_"), payload=payload)
            self.dhcp_agent_notifier.call(context, msg,
                                          topic=topics.DHCP_AGENT)
        return retval

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def evs_controller_getIPnet(self, ipnetuuid):
        try:
            ipnetlist = self._evsc.getIPnetInfo('ipnet=%s' % (ipnetuuid))
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)
        return (ipnetlist[0] if ipnetlist else None)

    def get_subnet(self, context, id, fields=None):
        ipnet = self.evs_controller_getIPnet(id)
        if not ipnet:
            return {}
        subnetdict = self._convert_ipnet_to_subnet(ipnet)
        return self._fields(subnetdict, fields)

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def evs_controller_getIPnetList(self, filterstr):
        try:
            ipnetlist = self._evsc.getIPnetInfo(filterstr)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)
        return ipnetlist

    def get_subnets(self, context, filters=None, fields=None,
                    sorts=None, limit=None, marker=None, page_reverse=False):

        filterstr = None
        # EVS desn't support filtering of resource based on
        # properties, so we will have to filter ourselves
        ipnet_props = {'OpenStack:enable_dhcp': None}
        if filters is not None:
            filterlist = []
            for key, value in filters.items():
                if key == 'shared':
                    if any(value):
                        return []
                    continue
                if key == 'verbose':
                    continue
                if key == 'enable_dhcp':
                    ipnet_props[SUBNET_IPNET_ATTRIBUTE_MAP[key]] = value
                    continue
                key = SUBNET_IPNET_ATTRIBUTE_MAP.get(key, key)
                if isinstance(value, list):
                    value = ",".join([str(val) for val in value])
                    if not value:
                        continue
                filterlist.append("%s=%s" % (key, value))

            if filterlist:
                filterstr = ",".join(filterlist)

        LOG.debug(_("calling ListIPnet from get_subnets() filterstr: '%s'")
                  % (filterstr))

        ipnetlist = self.evs_controller_getIPnetList(filterstr)
        self._apply_rsrc_props_filter(ipnetlist, ipnet_props)

        retme = []
        for ipnet in ipnetlist:
            subnetdict = self._convert_ipnet_to_subnet(ipnet)
            retme.append(self._fields(subnetdict, fields))

        return retme

    def get_subnets_count(self, context, filters=None):
        return len(self.get_subnets(context, filters))

    def _release_subnet_dhcp_port(self, context, subnet, delete_network):
        """Release any dhcp port associated with the subnet"""
        filters = dict(evs=subnet['network_id'])
        portlist = self.get_ports(context, filters)

        if delete_network:
            # One can delete a network if there is only one port that has a
            # VNIC attached to it and that port happens to be a DHCP port.
            ports_with_deviceid = [port for port in portlist
                                   if port['device_id'] != '']
            update_subnet = len(ports_with_deviceid) == 1
        else:
            # One can delete a subnet if there is only one port and that
            # port happens to be a DHCP port.
            update_subnet = len(portlist) == 1
        if update_subnet:
            # the lone port is a dhcp port created by dhcp agent
            # it must be released before we can delete the subnet
            subnet_update = {'subnet': {'enable_dhcp': False},
                             'evs_rpccall_sync': True}
            self.update_subnet(context, subnet['id'], subnet_update)

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def evs_controller_removeIPnet(self, tenantname, evsname, ipnetuuid):
        pat = radcli.ADRGlobPattern({'name': evsname, 'tenant': tenantname})
        try:
            evs = self._rc.get_object(evsbind.EVS(), pat)
            evs.removeIPnet(ipnetuuid)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)

    def delete_subnet(self, context, id):
        subnet = self.get_subnet(context, id)
        if not subnet:
            return

        # If the subnet is dhcp_enabled, then the dhcp agent would have
        # created a port connected to this subnet. We need to remove
        # that port before we can proceed with subnet delete operation.
        # Since, there is no subnet.delete.start event, we use an another
        # approach of updating the subnet's enable_dhcp attribute to
        # False that in turn sends a subnet.udpate notification. This
        # results in DHCP agent releasing the port.
        if subnet['enable_dhcp']:
                self._release_subnet_dhcp_port(context, subnet, False)
        self.evs_controller_removeIPnet(subnet['tenant_id'],
                                        subnet['network_id'], id)

        # notify dhcp agent
        payload = {
            'subnet': {
                'network_id': subnet['network_id'],
                'id': id,
            }
        }
        self.dhcp_agent_notifier.notify(context, payload, 'subnet.delete.end')

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def evs_controller_createEVS(self, tenantname, evsname, propstr):
        try:
            evs = self._evsc.createEVS(propstr, tenantname, evsname)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)
        return evs

    def create_network(self, context, network):
        """Creates a network(EVS) for a given tenant.

        An Elastic Virtual Switch (EVS) is a virtual switch that spans
        one or more servers (physical machines). It represents an isolated L2
        segment, and the isolation is implemented either through VLANs or
        VXLANs. An EVS provides network connectivity between the Virtual
        Machines connected to it. There are two main resources associated with
        an EVS: IPnet and VPort.
        """
        evsname = network['network']['name']
        if not evsname:
            evsname = None

        tenantname = self._get_tenant_id_for_create(context,
                                                    network['network'])
        proplist = []
        network_type = network['network'][providernet.NETWORK_TYPE]
        if attributes.is_attr_set(network_type):
            proplist.append('l2-type=%s' % network_type)

        segment_id = network['network'][providernet.SEGMENTATION_ID]
        if attributes.is_attr_set(segment_id):
            if (not attributes.is_attr_set(network_type) or
                    len(network_type) == 0):
                raise EVSControllerError(_("provider:network_type must be "
                                           "specified when provider:"
                                           "segmentation_id is provided"))

            if network_type == 'vxlan':
                proplist.append('vni=%d' % segment_id)
            elif network_type == 'vlan':
                proplist.append('vlanid=%d' % segment_id)
            else:
                raise EVSControllerError(_("specified "
                                           "provider:network_type '%s' not "
                                           "supported") % network_type)

        router_external = network['network'][external_net.EXTERNAL]
        if attributes.is_attr_set(router_external):
            proplist.append("%s=%s" %
                            (NETWORK_EVS_ATTRIBUTE_MAP[external_net.EXTERNAL],
                             router_external))

        propstr = None
        if proplist:
            propstr = ",".join(proplist)

        evs = self.evs_controller_createEVS(tenantname, evsname, propstr)
        return self._convert_evs_to_network(evs)

    def update_network(self, context, id, network):
        raise EVSOpNotSupported(_("net-update"))

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def evs_controller_getEVS(self, evsuuid):
        try:
            evslist = self._evsc.getEVSInfo('evs=%s' % evsuuid)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.getpayload().errmsg)
        return (evslist[0] if evslist else None)

    def get_network(self, context, id, fields=None):
        evs = self.evs_controller_getEVS(id)
        if not evs:
            return {}
        networkdict = self._convert_evs_to_network(evs)
        return self._fields(networkdict, fields)

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def evs_controller_getEVSList(self, filterstr):
        try:
            evslist = self._evsc.getEVSInfo(filterstr)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)
        return evslist

    def get_networks(self, context, filters=None, fields=None,
                     sorts=None, limit=None, marker=None, page_reverse=False):

        filterstr = None
        # EVS desn't support filtering of resource based on
        # properties, so we will have to filter ourselves
        evs_props = {'OpenStack:router:external': None}
        if filters is not None:
            filterlist = []
            for key, value in filters.items():
                if key == 'shared':
                    if any(value):
                        # EVS doesn't support shared networks
                        return []
                    continue
                if key in ('admin_state_up', 'verbose'):
                    continue
                if key == 'router:external':
                    evs_props[NETWORK_EVS_ATTRIBUTE_MAP[key]] = value
                    continue
                key = NETWORK_EVS_ATTRIBUTE_MAP.get(key, key)
                if isinstance(value, list):
                    value = ",".join([str(val) for val in value])
                    if not value:
                        continue
                filterlist.append("%s=%s" % (key, value))

            if filterlist:
                filterstr = ",".join(filterlist)

        LOG.debug(_("calling ListEVswitch from get_networks(): '%s'")
                  % (filterstr))
        evslist = self.evs_controller_getEVSList(filterstr)
        self._apply_rsrc_props_filter(evslist, evs_props)

        retme = []
        for evs in evslist:
            networkdict = self._convert_evs_to_network(evs)
            retme.append(self._fields(networkdict, fields))

        return retme

    def get_networks_count(self, context, filters=None):
        return len(self.get_networks(context, filters))

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def evs_controller_deleteEVS(self, tenantname, evsuuid):
        try:
            self._evsc.deleteEVS(evsuuid, tenantname)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)

    def delete_network(self, context, id):
        # Check if it is an external network and whether addresses in that
        # network are being used for floating ips
        evs = self.get_network(context, id)
        if evs[external_net.EXTERNAL]:
            filters = dict(evs=id)
            portlist = self.get_ports(context, filters)
            ports_with_deviceid = [port for port in portlist
                                   if port['device_id'] != '']
            if ports_with_deviceid:
                raise exceptions.NetworkInUse(net_id=id)
        filters = dict(network_id=id)
        subnets = self.get_subnets(context, filters=filters)
        dhcp_subnets = [s for s in subnets if s['enable_dhcp']]
        for subnet in dhcp_subnets:
            self._release_subnet_dhcp_port(context, subnet, True)
        self.evs_controller_deleteEVS(context.tenant_id, id)

        # notify dhcp agent of network deletion
        self.dhcp_agent_notifier.notify(context, {'network': {'id': id}},
                                        'network.delete.end')

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def evs_controller_addVPort(self, tenantname, evsname, vportname, propstr):
        try:
            pat = radcli.ADRGlobPattern({'name': evsname,
                                         'tenant': tenantname})
            evs = self._rc.get_object(evsbind.EVS(), pat)
            vport = evs.addVPort(propstr, vportname)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)
        return vport

    def create_port(self, context, port):
        """Creates a port(VPort) for a given network(EVS).

         A VPort represents the point of attachment between the VNIC and an
         EVS. It encapsulates various network configuration parameters such as
             -- SLAs (maxbw, cos, and priority)
             -- IP address and
             -- MAC address, et al
         This configuration is inherited by the VNIC when it connects to the
         VPort.
        """
        vportname = port['port']['name']
        if not vportname:
            vportname = None

        proplist = []
        macaddr = port['port']['mac_address']
        if attributes.is_attr_set(macaddr):
            proplist.append('macaddr=%s' % (macaddr))

        fixed_ips = port['port']['fixed_ips']
        if attributes.is_attr_set(fixed_ips):
            # we only support one subnet
            ipaddr = fixed_ips[0].get('ip_address')
            if ipaddr is not None:
                proplist.append('ipaddr=%s' % ipaddr)

        # retrieve device_id and device_owner
        device_id = port['port']['device_id']
        if attributes.is_attr_set(device_id) and device_id:
            proplist.append("%s=%s" %
                            (PORT_VPORT_ATTRIBUTE_MAP['device_id'], device_id))

        device_owner = port['port']['device_owner']
        if attributes.is_attr_set(device_owner) and device_owner:
            proplist.append("%s=%s" %
                            (PORT_VPORT_ATTRIBUTE_MAP['device_owner'],
                             device_owner))

        propstr = None
        if proplist:
            propstr = ",".join(proplist)

        evsname = port['port']['network_id']
        tenantname = self._get_tenant_id_for_create(context, port['port'])
        if (not tenantname and port['port']['device_owner'] ==
                l3_constants.DEVICE_OWNER_FLOATINGIP):
            network = self.get_network(context, evsname)
            tenantname = network['tenant_id']
        vport = self.evs_controller_addVPort(tenantname, evsname, vportname,
                                             propstr)
        retval = self._convert_vport_to_port(context, vport)

        # notify dhcp agent of port creation
        self.dhcp_agent_notifier.notify(context, {'port': retval},
                                        'port.create.end')
        return retval

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def evs_controller_updateVPort(self, vportuuid, proplist):
        try:
            pat = radcli.ADRGlobPattern({'uuid': vportuuid})
            vportlist = self._rc.list_objects(evsbind.VPort(), pat)
            assert len(vportlist) == 1
            vport = self._rc.get_object(vportlist[0])
            for prop in proplist:
                vport.setProperty(prop)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)

    def update_port(self, context, id, port):
        # EVS does not allow updating certain attributes
        if not (set(port['port'].keys()) <=
                set(('device_id', 'device_owner'))):
            raise EVSOpNotSupported(_("only device_id and "
                                      "device_owner supported"))

        proplist = []
        device_id = port['port'].get('device_id')
        if device_id is not None:
            # EVS expects property values to be non-zero length
            if len(device_id) == 0:
                device_id = " "
            proplist.append("%s=%s" %
                            (PORT_VPORT_ATTRIBUTE_MAP['device_id'], device_id))

        device_owner = port['port'].get('device_owner')
        if device_owner is not None:
            if len(device_owner) == 0:
                device_owner = " "
            proplist.append("%s=%s" %
                            (PORT_VPORT_ATTRIBUTE_MAP['device_owner'],
                             device_owner))

        if not proplist:
            return dict()

        self.evs_controller_updateVPort(id, proplist)
        retval = self.get_port(context, id)

        # notify dhcp agent of port update
        self.dhcp_agent_notifier.notify(context, {'port': retval},
                                        'port.update.end')
        return retval

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def evs_controller_getVPort(self, vportuuid):
        try:
            vportlist = self._evsc.getVPortInfo('vport=%s' % (vportuuid))
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)
        return (vportlist[0] if vportlist else None)

    def get_port(self, context, id, fields=None):
        vport = self.evs_controller_getVPort(id)
        if not vport:
            return {}
        portdict = self._convert_vport_to_port(context, vport)
        return self._fields(portdict, fields)

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def evs_controller_getVPortList(self, filterstr):
        try:
            vportlist = self._evsc.getVPortInfo(filterstr)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)
        return vportlist

    def get_ports(self, context, filters=None, fields=None,
                  sorts=None, limit=None, marker=None, page_reverse=False):
        LOG.debug(_("inside the get_ports() method: filters: '%s'") %
                  str(filters))

        filterstr = None
        # EVS desn't support filtering of resource based on
        # properties, so we will have to filter ourselves
        vport_props = {'OpenStack:device_id': None,
                       'OpenStack:device_owner': None}
        if filters is not None:
            filterlist = []
            for key, value in filters.items():
                if key == 'shared':
                    if any(value):
                        return []
                    continue
                if key == 'admin_state_up':
                    continue
                if key in ('device_id', 'device_owner'):
                    vport_props[PORT_VPORT_ATTRIBUTE_MAP[key]] = value
                    continue
                key = PORT_VPORT_ATTRIBUTE_MAP.get(key, key)
                if isinstance(value, list):
                    value = ",".join([str(val) for val in value])
                    if not value:
                        continue
                filterlist.append("%s=%s" % (key, value))

            if filterlist:
                filterstr = ",".join(filterlist)

        LOG.debug(_("calling getVPortInfo from get_ports(): '%s'") %
                  (filterstr))
        vportlist = self.evs_controller_getVPortList(filterstr)
        self._apply_rsrc_props_filter(vportlist, vport_props)

        retme = []
        for vport in vportlist:
            portdict = self._convert_vport_to_port(context, vport)
            retme.append(self._fields(portdict, fields))

        return retme

    def get_ports_count(self, context, filters=None):
        return len(self.get_ports(context, filters))

    def _release_l3agent_internal_port(self, context, port):
        """ If an L3 agent is using this port, then we need to send
        a notification to L3 agent to release the port before we can
        delete the port"""

        device_owner = port['device_owner']
        if device_owner not in [l3_constants.DEVICE_OWNER_ROUTER_INTF,
                                l3_constants.DEVICE_OWNER_ROUTER_GW,
                                l3_constants.DEVICE_OWNER_FLOATINGIP]:
            return
        router_id = port['device_id']
        port_update = {
            'port': {
                'device_id': '',
                'device_owner': ''
            }
        }
        self.update_port(context, port['id'], port_update)
        if device_owner in [l3_constants.DEVICE_OWNER_ROUTER_INTF,
                            l3_constants.DEVICE_OWNER_ROUTER_GW]:
            msg = l3_rpc_agent_api.L3AgentNotify.make_msg("routers_updated",
                                                          routers=[router_id])
            l3_rpc_agent_api.L3AgentNotify.call(context, msg,
                                                topic=topics.L3_AGENT)

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def evs_controller_removeVPort(self, tenantname, evsname, vportuuid):
        try:
            pat = radcli.ADRGlobPattern({'name': evsname,
                                         'tenant': tenantname})
            evs = self._rc.get_object(evsbind.EVS(), pat)
            evs.removeVPort(vportuuid)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)

    def delete_port(self, context, id, l3_port_check=True):
        if l3_port_check:
            self.prevent_l3_port_deletion(context, id)
        self.disassociate_floatingips(context, id)
        port = self.get_port(context, id)
        if not port:
            return
        if not l3_port_check:
            self._release_l3agent_internal_port(context, port)
        self.evs_controller_removeVPort(port['tenant_id'], port['network_id'],
                                        id)

        # notify dhcp agent of port deletion
        payload = {
            'port': {
                'network_id': port['network_id'],
                'id': id,
            }
        }
        self.dhcp_agent_notifier.notify(context, payload, 'port.delete.end')

    # needed for DHCP agent support
    def update_fixed_ip_lease_expiration(self, context, network_id,
                                         ip_address, lease_remaining):
        pass

    # needed for L3 agent support
    def _get_network(self, context, network_id):
        return self.get_network(context, network_id)

    def _get_subnet(self, context, subnet_id):
        return self.get_subnet(context, subnet_id)

    def _get_port(self, context, port_id):
        return self.get_port(context, port_id)

    def _delete_port(self, context, port_id):
        return self.delete_port(context, port_id)

    def _get_subnets_by_network(self, context, network_id):
        return self.get_subnets(context, filters={'network_id': network_id})

    def _network_is_external(self, context, net_id):
        try:
            evs = self.get_network(context, net_id)
            return evs[external_net.EXTERNAL]
        except:
            return False
