# vim: tabstop=4 shiftwidth=4 softtabstop=4

# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
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

import rad.client as radcli
import rad.connect as radcon
import rad.bindings.com.oracle.solaris.rad.evscntl_1 as evsbind

from oslo_concurrency import lockutils
from oslo_config import cfg
from oslo_db import api as oslo_db_api
from oslo_log import log as logging
from oslo_utils import importutils

from neutron.api.rpc.agentnotifiers import dhcp_rpc_agent_api
from neutron.api.rpc.agentnotifiers import l3_rpc_agent_api
from neutron.api.rpc.handlers import dhcp_rpc
from neutron.api.rpc.handlers import l3_rpc
from neutron.api.rpc.handlers import metadata_rpc
from neutron.api.v2 import attributes
from neutron.common import constants
from neutron.common import exceptions
from neutron.common import rpc as n_rpc
from neutron.common import topics
from neutron.db import agents_db
from neutron.db import agentschedulers_db
from neutron.db import api as db
from neutron.db import db_base_plugin_v2
from neutron.db import external_net_db
from neutron.db import l3_agentschedulers_db
from neutron.db import l3_attrs_db
from neutron.db import l3_gwmode_db
from neutron.db import models_v2
from neutron.db import portbindings_db
from neutron.db import quota_db
from neutron.db import securitygroups_db
from neutron.extensions import external_net
from neutron.extensions import providernet
from neutron.plugins.common import constants as svc_constants
from neutron.plugins.ml2 import models

LOG = logging.getLogger(__name__)
# Only import the vpn server code if it exists.
try:
    sp = cfg.CONF.service_plugins
    vpns = 'vpnaas'
    if vpns in sp:
        try:
            from neutron_vpnaas.db.vpn import vpn_db
            LOG.debug("Loading VPNaaS service driver.")
        except ImportError:
            pass
    else:
        LOG.debug("vpnaas service_plugin not configured")
except:
    pass

evs_controller_opts = [
    cfg.StrOpt('evs_controller', default='ssh://evsuser@localhost',
               help=_("An URI that specifies an EVS controller"))
]

cfg.CONF.register_opts(evs_controller_opts, "EVS")


class EVSControllerError(exceptions.NeutronException):
    message = _("EVS controller: %(errmsg)s")

    def __init__(self, evs_errmsg):
        super(EVSControllerError, self).__init__(errmsg=evs_errmsg)


class EVSOpNotSupported(exceptions.NeutronException):
    message = _("Operation not supported by EVS plugin: %(opname)s")

    def __init__(self, evs_errmsg):
        super(EVSOpNotSupported, self).__init__(opname=evs_errmsg)


class EVSNotFound(exceptions.NeutronException):
    message = _("Network %(net_id)s could not be found in EVS")


class EVSNeutronPluginV2(db_base_plugin_v2.NeutronDbPluginV2,
                         agentschedulers_db.DhcpAgentSchedulerDbMixin,
                         external_net_db.External_net_db_mixin,
                         l3_agentschedulers_db.L3AgentSchedulerDbMixin,
                         l3_gwmode_db.L3_NAT_db_mixin):
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

    _supported_extension_aliases = ["provider", "external-net", "router",
                                    "ext-gw-mode", "quotas", "agent",
                                    "l3_agent_scheduler",
                                    "dhcp_agent_scheduler"]

    def __init__(self):
        self.network_scheduler = importutils.import_object(
            cfg.CONF.network_scheduler_driver
        )
        self.router_scheduler = importutils.import_object(
            cfg.CONF.router_scheduler_driver
        )
        self._setup_rpc()
        self._rad_connection = None

    @property
    def rad_connection(self):
        # Since there is no connect_uri() yet, we need to do
        # parsing of ssh://user@hostname ourselves
        suh = cfg.CONF.EVS.evs_controller.split('://')
        if len(suh) != 2 or suh[0] != 'ssh' or not suh[1].strip():
            raise SystemExit(_("Specified evs_controller is invalid"))
        uh = suh[1].split('@')
        if len(uh) != 2 or not uh[0].strip() or not uh[1].strip():
            raise SystemExit(_("'user' and 'hostname' need to be specified "
                               "for evs_controller"))

        if (self._rad_connection is not None and
                self._rad_connection._closed is None):
            return self._rad_connection

        LOG.debug(_("Connecting to EVS Controller at %s as %s") %
                  (uh[1], uh[0]))
        self._rad_connection = radcon.connect_ssh(uh[1], user=uh[0])
        return self._rad_connection

    def _setup_rpc(self):
        # RPC support
        self.service_topics = {svc_constants.CORE: topics.PLUGIN,
                               svc_constants.L3_ROUTER_NAT: topics.L3PLUGIN}
        self.conn = n_rpc.create_connection(new=True)
        self.endpoints = [dhcp_rpc.DhcpRpcCallback(),
                          l3_rpc.L3RpcCallback(),
                          agents_db.AgentExtRpcCallback(),
                          metadata_rpc.MetadataRpcCallback()]
        for svc_topic in self.service_topics.values():
            self.conn.create_consumer(svc_topic, self.endpoints, fanout=False)
        # Consume from all consumers in a thread
        self.conn.consume_in_threads()
        self.dhcp_agent_notifier = dhcp_rpc_agent_api.DhcpAgentNotifyAPI()
        self.l3_agent_notifier = l3_rpc_agent_api.L3AgentNotifyAPI()

        # needed by AgentSchedulerDbMixin()
        self.agent_notifiers[constants.AGENT_TYPE_DHCP] = \
            self.dhcp_agent_notifier
        self.agent_notifiers[constants.AGENT_TYPE_L3] = \
            self.l3_agent_notifier

    @property
    def supported_extension_aliases(self):
        return self._supported_extension_aliases

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def _evs_controller_addIPnet(self, tenantname, evsname, ipnetname,
                                 propstr):
        LOG.debug(_("Adding IPnet: %s with properties: %s for tenant: %s "
                    "and for evs: %s") %
                  (ipnetname, propstr, tenantname, evsname))

        pat = radcli.ADRGlobPattern({'name': evsname,
                                     'tenant': tenantname})
        try:
            evs = self.rad_connection.get_object(evsbind.EVS(), pat)
            ipnet = evs.addIPnet(propstr, ipnetname)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)
        return ipnet

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def _evs_controller_updateIPnet(self, ipnetuuid, propstr):
        LOG.debug(_("Updating IPnet with id: %s with property string: %s") %
                  (ipnetuuid, propstr))
        pat = radcli.ADRGlobPattern({'uuid': ipnetuuid})
        try:
            ipnetlist = self.rad_connection.list_objects(evsbind.IPnet(), pat)
            if not ipnetlist:
                return
            assert len(ipnetlist) == 1
            ipnet = self.rad_connection.get_object(ipnetlist[0])
            ipnet.setProperty(propstr)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)

    def _subnet_pool_to_evs_pool(self, subnet):
        poolstr = ""
        # obtain the optional allocation pool
        pools = subnet.get('allocation_pools')
        if not pools or pools is attributes.ATTR_NOT_SPECIFIED:
            return poolstr

        for pool in pools:
            if poolstr:
                poolstr += ","
            # if start and end address is same, EVS expects the address
            # to be provided as-is instead of x.x.x.x-x.x.x.x
            if pool['start'] == pool['end']:
                poolstr += pool['start']
            else:
                poolstr += "%s-%s" % (pool['start'], pool['end'])
        return poolstr

    def create_subnet(self, context, subnet):
        """Creates a subnet(IPnet) for a given network(EVS).

         An IP network represents a block of either IPv4 or IPv6 addresses
         (i.e., subnet) along with a default router for the block. Only one
         IPnet can be associated with an EVS. All the zones/VNICs that
         connect to the EVS, through a VPort, will get an IP address from the
         IPnet associated with the EVS.
        """

        if (subnet['subnet']['host_routes'] is not
                attributes.ATTR_NOT_SPECIFIED):
            raise EVSOpNotSupported(_("setting --host-route for a subnet "
                                      "not supported"))

        poolstr = self._subnet_pool_to_evs_pool(subnet['subnet'])

        with context.session.begin(subtransactions=True):
            # create the subnet in the DB
            db_subnet = super(EVSNeutronPluginV2, self).create_subnet(context,
                                                                      subnet)
            ipnetname = db_subnet['name']
            if not ipnetname:
                ipnetname = None
            evsname = db_subnet['network_id']
            tenantname = db_subnet['tenant_id']
            proplist = ['subnet=%s' % db_subnet['cidr']]
            defrouter = db_subnet['gateway_ip']
            if not defrouter:
                defrouter = '0.0.0.0' if db_subnet['ip_version'] == 4 else '::'
            proplist.append('defrouter=%s' % defrouter)
            proplist.append('uuid=%s' % db_subnet['id'])
            if poolstr:
                proplist.append('pool=%s' % (poolstr))
            self._evs_controller_addIPnet(tenantname, evsname, ipnetname,
                                          ",".join(proplist))

        return db_subnet

    def update_subnet(self, context, id, subnet):
        LOG.debug(_("Updating Subnet: %s with %s") % (id, subnet))
        if (set(subnet['subnet'].keys()) - set(('enable_dhcp',
                                                'allocation_pools',
                                                'dns_nameservers',
                                                'ipv6_address_mode',
                                                'ipv6_ra_mode'))):
                raise EVSOpNotSupported(_("only following subnet attributes "
                                          "enable-dhcp, allocation-pool, "
                                          "dns-nameserver, ipv6-address-mode, "
                                          "and ipv6-ra-mode can be updated"))

        poolstr = self._subnet_pool_to_evs_pool(subnet['subnet'])

        with context.session.begin(subtransactions=True):
            # update subnet in DB
            retval = super(EVSNeutronPluginV2, self).\
                update_subnet(context, id, subnet)
            # update EVS IPnet with allocation pool info
            if poolstr:
                self._evs_controller_updateIPnet(id, "pool=%s" % poolstr)

        return retval

    def get_subnet(self, context, id, fields=None):
        LOG.debug(_("Getting subnet: %s"), id)
        subnet = super(EVSNeutronPluginV2, self).get_subnet(context, id, None)
        return self._fields(subnet, fields)

    def get_subnets(self, context, filters=None, fields=None,
                    sorts=None, limit=None, marker=None, page_reverse=False):
        subnets = super(EVSNeutronPluginV2, self).\
            get_subnets(context, filters, None, sorts, limit, marker,
                        page_reverse)
        return [self._fields(subnet, fields) for subnet in subnets]

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def _evs_controller_removeIPnet(self, tenantname, evsname, ipnetuuid,
                                    auto_created_ports):
        LOG.debug(_("Removing IPnet with id: %s for tenant: %s for evs: %s") %
                  (ipnetuuid, tenantname, evsname))
        pat = radcli.ADRGlobPattern({'name': evsname, 'tenant': tenantname})
        try:
            evs = self.rad_connection.get_object(evsbind.EVS(), pat)
            if auto_created_ports:
                LOG.debug(_("Need to remove following ports %s before "
                            "removing the IPnet") % (auto_created_ports))
                for port in auto_created_ports:
                    try:
                        evs.removeVPort(port['id'], "force=yes")
                    except radcli.ObjectError as oe:
                        # '43' corresponds to EVS' EVS_ENOENT_VPORT error code
                        if oe.get_payload().err == 43:
                            LOG.debug(_("VPort %s could not be found") %
                                      (port['id']))
            evs.removeIPnet(ipnetuuid)
        except (radcli.NotFoundError, radcli.ObjectError) as oe:
            # '42' corresponds to EVS' EVS_ENOENT_IPNET error code
            if oe.get_payload() is None or oe.get_payload().err == 42:
                # EVS doesn't have that IPnet, return success to delete
                # the IPnet from Neutron DB.
                LOG.debug(_("IPnet could not be found in EVS."))
                return
            raise EVSControllerError(oe.get_payload().errmsg)

    def delete_subnet(self, context, id):
        subnet = self.get_subnet(context, id)
        if not subnet:
            return

        with context.session.begin(subtransactions=True):
            # get a list of ports automatically created by Neutron
            auto_created_ports = context.session.query(models_v2.Port).\
                filter(models_v2.Port.device_owner.
                       in_(db_base_plugin_v2.AUTO_DELETE_PORT_OWNERS)).all()
            # delete subnet in DB
            super(EVSNeutronPluginV2, self).delete_subnet(context, id)
            self._evs_controller_removeIPnet(subnet['tenant_id'],
                                             subnet['network_id'], id,
                                             auto_created_ports)

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def _evs_controller_createEVS(self, tenantname, evsname, propstr):
        LOG.debug(_("Adding EVS: %s with properties: %s for tenant: %s") %
                  (evsname, propstr, tenantname))
        try:
            evs = self.rad_connection.\
                get_object(evsbind.EVSController()).\
                createEVS(propstr, tenantname, evsname)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)
        return evs

    def _extend_network_dict(self, network, evs):
        for prop in evs.props:
            if prop.name == 'l2-type':
                network[providernet.NETWORK_TYPE] = prop.value
            elif prop.name == 'vlanid' or prop.name == 'vni':
                network[providernet.SEGMENTATION_ID] = int(prop.value)

    def create_network(self, context, network):
        """Creates a network(EVS) for a given tenant.

        An Elastic Virtual Switch (EVS) is a virtual switch that spans
        one or more servers (physical machines). It represents an isolated L2
        segment, and the isolation is implemented either through VLANs or
        VXLANs. An EVS provides network connectivity between the Virtual
        Machines connected to it. There are two main resources associated with
        an EVS: IPnet and VPort.
        """

        if network['network']['admin_state_up'] is False:
            raise EVSOpNotSupported(_("setting admin_state_up=False for a "
                                      "network not supported"))

        if network['network']['shared'] is True:
            raise EVSOpNotSupported(_("setting shared=True for a "
                                      "network not supported"))

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

        propstr = None
        if proplist:
            propstr = ",".join(proplist)

        with context.session.begin(subtransactions=True):
            # create the network in DB
            net = super(EVSNeutronPluginV2, self).create_network(context,
                                                                 network)
            self._process_l3_create(context, net, network['network'])
            # if --router:external is not set, the above function does
            # not update net with router:external set to False
            if net.get(external_net.EXTERNAL) is None:
                net[external_net.EXTERNAL] = False

            # create EVS on the EVS controller
            if propstr:
                propstr += ",uuid=%s" % net['id']
            else:
                propstr = "uuid=%s" % net['id']
            evs = self._evs_controller_createEVS(tenantname, evsname, propstr)

            # add provider information into net
            self._extend_network_dict(net, evs)

        return net

    def update_network(self, context, id, network):
        raise EVSOpNotSupported(_("net-update"))

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def _evs_controller_getEVS(self, evsuuid):
        LOG.debug(_("Getting EVS: %s"), evsuuid)
        try:
            evslist = self.rad_connection.\
                get_object(evsbind.EVSController()).\
                getEVSInfo('evs=%s' % evsuuid)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.getpayload().errmsg)
        if not evslist:
            LOG.error(_("EVS framework does not have Neutron network "
                        "'%s' defined"), evsuuid)
            return None
        return evslist[0]

    def get_network(self, context, id, fields=None):
        with context.session.begin(subtransactions=True):
            net = super(EVSNeutronPluginV2, self).get_network(context,
                                                              id, None)
            # call EVS controller to get provider network information
            evs = self._evs_controller_getEVS(net['id'])
            if evs:
                self._extend_network_dict(net, evs)
        return self._fields(net, fields)

    def get_networks(self, context, filters=None, fields=None,
                     sorts=None, limit=None, marker=None, page_reverse=False):

        with context.session.begin(subtransactions=True):
            nets = super(EVSNeutronPluginV2, self).\
                get_networks(context, filters, None, sorts, limit, marker,
                             page_reverse)
            for net in nets:
                evs = self._evs_controller_getEVS(net['id'])
                if evs:
                    self._extend_network_dict(net, evs)
        return [self._fields(net, fields) for net in nets]

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def _evs_controller_deleteEVS(self, tenantname, evsuuid):
        LOG.debug(_("Removing EVS with id: %s for tenant: %s") %
                  (evsuuid, tenantname))
        try:
            self.rad_connection.\
                get_object(evsbind.EVSController()).\
                deleteEVS(evsuuid, tenantname)
        except (radcli.NotFoundError, radcli.ObjectError) as oe:
            # '41' corresponds to EVS' EVS_ENOENT_EVS error code
            if oe.get_payload() is None or oe.get_payload().err == 41:
                # EVS doesn't have that EVS, return success to delete
                # the EVS from Neutron DB.
                LOG.debug(_("EVS could not be found in EVS backend."))
                return
            raise EVSControllerError(oe.get_payload().errmsg)

    def delete_network(self, context, id):
        with context.session.begin(subtransactions=True):
            network = self._get_network(context, id)

            qry_network_ports = context.session.query(models_v2.Port).\
                filter_by(network_id=id).filter(models_v2.Port.device_owner.
                                                in_(db_base_plugin_v2.
                                                    AUTO_DELETE_PORT_OWNERS))

            auto_created_ports = qry_network_ports.all()
            qry_network_ports.delete(synchronize_session=False)

            port_in_use = context.session.query(models_v2.Port).filter_by(
                network_id=id).first()

            if port_in_use:
                raise exceptions.NetworkInUse(net_id=id)

            # clean up subnets
            subnets = self._get_subnets_by_network(context, id)
            for subnet in subnets:
                super(EVSNeutronPluginV2, self).delete_subnet(context,
                                                              subnet['id'])
                self._evs_controller_removeIPnet(subnet['tenant_id'],
                                                 subnet['network_id'],
                                                 subnet['id'],
                                                 auto_created_ports)

            context.session.delete(network)
            self._evs_controller_deleteEVS(network['tenant_id'], id)

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def _evs_controller_addVPort(self, tenantname, evsname, vportname,
                                 propstr):
        LOG.debug(_("Adding VPort: %s with properties: %s for tenant: %s "
                    "and for evs: %s") %
                  (vportname, propstr, tenantname, evsname))

        try:
            pat = radcli.ADRGlobPattern({'name': evsname,
                                         'tenant': tenantname})
            evs = self.rad_connection.get_object(evsbind.EVS(), pat)
            vport = evs.addVPort(propstr, vportname)
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)
        return vport

    @oslo_db_api.wrap_db_retry(max_retries=db.MAX_RETRIES,
                               retry_on_request=True,
                               retry_on_deadlock=True)
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
        if port['port']['admin_state_up'] is False:
            raise EVSOpNotSupported(_("setting admin_state_up=False for a "
                                      "port not supported"))

        with context.session.begin(subtransactions=True):
            # for external gateway ports and floating ips, tenant_id
            # is not set, but EVS does not like it.
            tenant_id = self._get_tenant_id_for_create(context, port['port'])
            if not tenant_id:
                network = self._get_network(context,
                                            port['port']['network_id'])
                port['port']['tenant_id'] = network['tenant_id']
            # create the port in the DB
            db_port = super(EVSNeutronPluginV2, self).create_port(context,
                                                                  port)
            # Neutron allows to create a port on a network that doesn't
            # yet have subnet associated with it, however EVS doesn't
            # support this.
            if not db_port['fixed_ips']:
                raise EVSOpNotSupported(_("creating a port on a network that "
                                          "does not yet have subnet "
                                          "associated with it is not "
                                          "supported"))
            tenantname = db_port['tenant_id']
            vportname = db_port['name']
            if not vportname:
                vportname = None
            evs_id = db_port['network_id']
            proplist = ['macaddr=%s' % db_port['mac_address']]
            proplist.append('ipaddr=%s' %
                            db_port['fixed_ips'][0].get('ip_address'))
            proplist.append('uuid=%s' % db_port['id'])

            self._evs_controller_addVPort(tenantname, evs_id, vportname,
                                          ",".join(proplist))
        return db_port

    def update_port(self, context, id, port):
        # EVS does not allow updating certain attributes, so check for it
        state = port['port'].get('admin_state_up')
        if state and state is False:
            raise EVSOpNotSupported(_("updating port's admin_state_up to "
                                      "False is not supported"))

        # Get the original port and fail if any attempt is being made
        # to change fixed_ips of the port since EVS doesn't support it
        original_port = super(EVSNeutronPluginV2, self).get_port(context, id)
        original_ips = original_port['fixed_ips']
        update_ips = port['port'].get('fixed_ips')
        if (update_ips and
            (len(update_ips) != 1 or
             update_ips[0]['subnet_id'] != original_ips[0]['subnet_id'] or
             update_ips[0]['ip_address'] != original_ips[0]['ip_address'])):
            raise EVSOpNotSupported(_("updating port's fixed_ips "
                                      "is not supported"))
        LOG.debug(_("Updating port %s with %s") % (id, port))
        db_port = super(EVSNeutronPluginV2, self).update_port(context,
                                                              id, port)
        return db_port

    def get_port(self, context, id, fields=None):
        LOG.debug(_("Getting port: %s"), id)
        port = super(EVSNeutronPluginV2, self).get_port(context, id, None)
        return self._fields(port, fields)

    def get_ports(self, context, filters=None, fields=None,
                  sorts=None, limit=None, marker=None, page_reverse=False):
        ports = super(EVSNeutronPluginV2, self).\
            get_ports(context, filters, None, sorts, limit, marker,
                      page_reverse)
        return [self._fields(port, fields) for port in ports]

    @lockutils.synchronized('evs-plugin', 'neutron-')
    def _evs_controller_removeVPort(self, tenantname, evsname, vportuuid):
        LOG.debug(_("Removing VPort with id: %s for tenant: %s for evs: %s") %
                  (vportuuid, tenantname, evsname))
        pat = radcli.ADRGlobPattern({'name': evsname,
                                     'tenant': tenantname})
        try:
            evs = self.rad_connection.get_object(evsbind.EVS(), pat)
            evs.removeVPort(vportuuid, "force=yes")
        except (radcli.NotFoundError, radcli.ObjectError) as oe:
            # '43' corresponds to EVS' EVS_ENOENT_VPORT error code
            if oe.get_payload() is None or oe.get_payload().err == 43:
                # EVS doesn't have that VPort, return success to delete
                # the VPort from Neutron DB.
                LOG.debug(_("VPort could not be found in EVS."))
            else:
                raise EVSControllerError(oe.get_payload().errmsg)

    def delete_port(self, context, id, l3_port_check=True):
        if l3_port_check:
            self.prevent_l3_port_deletion(context, id)
        self.disassociate_floatingips(context, id)
        port = self.get_port(context, id)
        if not port:
            return
        with context.session.begin(subtransactions=True):
            super(EVSNeutronPluginV2, self).delete_port(context, id)
            self._evs_controller_removeVPort(port['tenant_id'],
                                             port['network_id'],
                                             port['id'])
