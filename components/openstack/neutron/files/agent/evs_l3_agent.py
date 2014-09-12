# vim: tabstop=4 shiftwidth=4 softtabstop=4

# Copyright 2012 Nicira Networks, Inc.  All rights reserved.
#
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
# @author: Dan Wendlandt, Nicira, Inc
# @author: Girish Moodalbail, Oracle, Inc.
#

"""
Based off generic l3_agent (neutron/agent/l3_agent) code
"""

import netaddr

from oslo.config import cfg

from neutron.agent import l3_agent
from neutron.agent.linux import utils
from neutron.agent.solaris import interface
from neutron.agent.solaris import ipfilters_manager
from neutron.agent.solaris import net_lib
from neutron.common import constants as l3_constants
from neutron.openstack.common import log as logging


LOG = logging.getLogger(__name__)
INTERNAL_DEV_PREFIX = 'l3i'
EXTERNAL_DEV_PREFIX = 'l3e'
FLOATING_IP_CIDR_SUFFIX = '/32'


class RouterInfo(object):

    def __init__(self, router_id, root_helper, use_namespaces, router):
        self.router_id = router_id
        self.ex_gw_port = None
        self._snat_enabled = None
        self._snat_action = None
        self.internal_ports = []
        # We do not need either root_helper or namespace, so set them to None
        self.root_helper = None
        self.use_namespaces = None
        # Invoke the setter for establishing initial SNAT action
        self.router = router
        self.ipfilters_manager = ipfilters_manager.IPfiltersManager()
        self.routes = []

    @property
    def router(self):
        return self._router

    @router.setter
    def router(self, value):
        self._router = value
        if not self._router:
            return
        # enable_snat by default if it wasn't specified by plugin
        self._snat_enabled = self._router.get('enable_snat', True)
        # Set a SNAT action for the router
        if self._router.get('gw_port'):
            self._snat_action = ('add_rules' if self._snat_enabled
                                 else 'remove_rules')
        elif self.ex_gw_port:
            # Gateway port was removed, remove rules
            self._snat_action = 'remove_rules'

    def ns_name(self):
        pass

    def perform_snat_action(self, snat_callback, *args):
        # Process SNAT rules for attached subnets
        if self._snat_action:
            snat_callback(self, self._router.get('gw_port'),
                          *args, action=self._snat_action)
        self._snat_action = None


class EVSL3NATAgent(l3_agent.L3NATAgent):

    RouterInfo = RouterInfo

    OPTS = [
        cfg.StrOpt('external_network_datalink', default='net0',
                   help=_("Name of the datalink that connects to "
                          "an external network.")),
        cfg.BoolOpt('allow_forwarding_between_networks', default=False,
                    help=_("Allow forwarding of packets between tenant's "
                           "networks")),
    ]

    def __init__(self, host, conf=None):
        cfg.CONF.register_opts(self.OPTS)
        cfg.CONF.register_opts(interface.OPTS)
        super(EVSL3NATAgent, self).__init__(host=host, conf=conf)

    def _router_added(self, router_id, router):
        ri = RouterInfo(router_id, self.root_helper,
                        self.conf.use_namespaces, router)
        self.router_info[router_id] = ri

    def _router_removed(self, router_id):
        ri = self.router_info[router_id]
        ri.router['gw_port'] = None
        ri.router[l3_constants.INTERFACE_KEY] = []
        ri.router[l3_constants.FLOATINGIP_KEY] = []
        self.process_router(ri)
        del self.router_info[router_id]

    def process_router(self, ri):
        ex_gw_port = self._get_ex_gw_port(ri)
        internal_ports = ri.router.get(l3_constants.INTERFACE_KEY, [])
        existing_port_ids = set([p['id'] for p in ri.internal_ports])
        current_port_ids = set([p['id'] for p in internal_ports
                                if p['admin_state_up']])
        new_ports = [p for p in internal_ports if
                     p['id'] in current_port_ids and
                     p['id'] not in existing_port_ids]
        old_ports = [p for p in ri.internal_ports if
                     p['id'] not in current_port_ids]
        for p in new_ports:
            self._set_subnet_info(p)
            ri.internal_ports.append(p)
            self.internal_network_added(ri, p)

        for p in old_ports:
            ri.internal_ports.remove(p)
            self.internal_network_removed(ri, p)

        internal_cidrs = [p['ip_cidr'] for p in ri.internal_ports]
        # TODO(salv-orlando): RouterInfo would be a better place for
        # this logic too
        ex_gw_port_id = (ex_gw_port and ex_gw_port['id'] or
                         ri.ex_gw_port and ri.ex_gw_port['id'])

        interface_name = None
        if ex_gw_port_id:
            interface_name = self.get_external_device_name(ex_gw_port_id)
        if ex_gw_port and not ri.ex_gw_port:
            self._set_subnet_info(ex_gw_port)
            self.external_gateway_added(ri, ex_gw_port,
                                        interface_name, internal_cidrs)
        elif not ex_gw_port and ri.ex_gw_port:
            self.external_gateway_removed(ri, ri.ex_gw_port,
                                          interface_name, internal_cidrs)

        # We don't need this since our IPnat rules are bi-directional
        # Process SNAT rules for external gateway
        # ri.perform_snat_action(self._handle_router_snat_rules,
        #                       internal_cidrs, interface_name)

        # Process DNAT rules for floating IPs
        if ex_gw_port:
            self.process_router_floating_ips(ri, ex_gw_port)

        ri.ex_gw_port = ex_gw_port
        ri.enable_snat = ri.router.get('enable_snat')
        self.routes_updated(ri)

    def process_router_floating_ips(self, ri, ex_gw_port):
        """Configure the router's floating IPs
        Configures floating ips using ipnat(1m) on the router's gateway device.

        Cleans up floating ips that should not longer be configured.
        """
        ifname = self.get_external_device_name(ex_gw_port['id'])
        ipintf = net_lib.IPInterface(ifname)
        ipaddr_list = ipintf.ipaddr_list()['static']

        existing_cidrs = set([addr for addr in ipaddr_list])
        new_cidrs = set()

        existing_nat_rules = [nat_rule for nat_rule in
                              ri.ipfilters_manager.ipv4['nat']]
        new_nat_rules = []

        # Loop once to ensure that floating ips are configured.
        for fip in ri.router.get(l3_constants.FLOATINGIP_KEY, []):
            fip_ip = fip['floating_ip_address']
            fip_cidr = str(fip_ip) + FLOATING_IP_CIDR_SUFFIX
            new_cidrs.add(fip_cidr)
            fixed_cidr = str(fip['fixed_ip_address']) + '/32'
            nat_rule = 'bimap %s %s -> %s' % (ifname, fixed_cidr, fip_cidr)

            if fip_cidr not in existing_cidrs:
                ipintf.create_address(fip_cidr)
                ri.ipfilters_manager.add_nat_rules([nat_rule])
            new_nat_rules.append(nat_rule)

        # remove all the old NAT rules
        ri.ipfilters_manager.remove_nat_rules(list(set(existing_nat_rules) -
                                              set(new_nat_rules)))

        # Clean up addresses that no longer belong on the gateway interface.
        for ip_cidr in existing_cidrs - new_cidrs:
            if ip_cidr.endswith(FLOATING_IP_CIDR_SUFFIX):
                ipintf.delete_address(ip_cidr)

    def get_internal_device_name(self, port_id):
        # Because of the way how dnsmasq works on Solaris, the length
        # of datalink name cannot exceed 16 (includes terminating nul
        # character). So, the linkname can only have 15 characters and
        # the last two characters are set aside for '_0'. So, we only
        # have 13 characters left.
        dname = (INTERNAL_DEV_PREFIX + port_id)[:13]
        dname += '_0'
        return dname.replace('-', '_')

    def get_external_device_name(self, port_id):
        # please see the comment above
        dname = (EXTERNAL_DEV_PREFIX + port_id)[:13]
        dname += '_0'
        return dname.replace('-', '_')

    def external_gateway_added(self, ri, ex_gw_port,
                               external_dlname, internal_cidrs):

        if not net_lib.Datalink.datalink_exists(external_dlname):
            dl = net_lib.Datalink(external_dlname)
            # need to determine the VLAN ID for the VNIC
            evsname = ex_gw_port['network_id']
            tenantname = ex_gw_port['tenant_id']
            cmd = ['/usr/sbin/evsadm', 'show-evs', '-co', 'vid',
                   '-f', 'tenant=%s' % tenantname, evsname]
            try:
                stdout = utils.execute(cmd)
            except Exception as err:
                LOG.error(_("Failed to retrieve the VLAN ID associated "
                            "with the external network, and it is required "
                            "to create external gateway port: %s") % err)
                return
            vid = stdout.splitlines()[0].strip()
            if vid == "":
                LOG.error(_("External Network does not have a VLAN ID "
                            "associated with it, and it is required to "
                            "create external gateway port"))
                return
            mac_address = ex_gw_port['mac_address']
            dl.create_vnic(self.conf.external_network_datalink,
                           mac_address=mac_address, vid=vid)
        self.driver.init_l3(external_dlname, [ex_gw_port['ip_cidr']])

        # TODO(gmoodalb): wrap route(1m) command within a class in net_lib.py
        gw_ip = ex_gw_port['subnet']['gateway_ip']
        if gw_ip:
            cmd = ['/usr/bin/pfexec', '/usr/sbin/route', 'add', 'default',
                   gw_ip]
            utils.execute(cmd, check_exit_code=False)

            # for each of the internal ports, add Policy Based
            # Routing (PBR) rule
            for port in ri.internal_ports:
                internal_dlname = self.get_internal_device_name(port['id'])
                rules = ['pass in on %s to %s:%s from any to any' %
                         (internal_dlname, external_dlname, gw_ip)]
                ipversion = netaddr.IPNetwork(port['subnet']['cidr']).version
                ri.ipfilters_manager.add_ipf_rules(rules, ipversion)

    def external_gateway_removed(self, ri, ex_gw_port,
                                 external_dlname, internal_cidrs):

        gw_ip = ex_gw_port['subnet']['gateway_ip']
        if gw_ip:
            # remove PBR rules
            for port in ri.internal_ports:
                internal_dlname = self.get_internal_device_name(port['id'])
                rules = ['pass in on %s to %s:%s from any to any' %
                         (internal_dlname, external_dlname, gw_ip)]
                ipversion = netaddr.IPNetwork(port['subnet']['cidr']).version
                ri.ipfilters_manager.remove_ipf_rules(rules, ipversion)

            cmd = ['/usr/bin/pfexec', '/usr/sbin/route', 'delete', 'default',
                   gw_ip]
            utils.execute(cmd, check_exit_code=False)

        if net_lib.Datalink.datalink_exists(external_dlname):
            self.driver.fini_l3(external_dlname)
            self.driver.unplug(external_dlname)

    def _get_ippool_name(self, mac_address, suffix=None):
        # Generate a unique-name for ippool(1m) from that last 3
        # bytes of mac-address. It is called pool name, but it is
        # actually a 32 bit integer
        name = mac_address.split(':')[3:]
        if suffix:
            name.append(suffix)
        return int("".join(name), 16)

    def internal_network_added(self, ri, port):
        internal_dlname = self.get_internal_device_name(port['id'])
        # driver just returns if datalink and IP interface already exists
        self.driver.plug(port['tenant_id'], port['network_id'], port['id'],
                         internal_dlname)
        self.driver.init_l3(internal_dlname, [port['ip_cidr']])

        # Since we support shared router model, we need to block the new
        # internal port from reaching other tenant's ports
        block_pname = self._get_ippool_name(port['mac_address'])
        ri.ipfilters_manager.add_ippool(block_pname, None)
        if self.conf.allow_forwarding_between_networks:
            # If allow_forwarding_between_networks is set, then we need to
            # allow forwarding of packets between same tenant's ports.
            allow_pname = self._get_ippool_name(port['mac_address'], '0')
            ri.ipfilters_manager.add_ippool(allow_pname, None)

        # walk through the other internal ports and retrieve their
        # cidrs and at the same time add the new internal port's
        # cidr to them
        port_subnet = port['subnet']['cidr']
        block_subnets = []
        allow_subnets = []
        for internal_port in ri.internal_ports:
            if internal_port['mac_address'] == port['mac_address']:
                continue
            if (self.conf.allow_forwarding_between_networks and
                    internal_port['tenant_id'] == port['tenant_id']):
                allow_subnets.append(internal_port['subnet']['cidr'])
                # we need to add the port's subnet to this internal_port's
                # allowed_subnet_pool
                iport_allow_pname = \
                    self._get_ippool_name(internal_port['mac_address'], '0')
                ri.ipfilters_manager.add_ippool(iport_allow_pname,
                                                [port_subnet])
            else:
                block_subnets.append(internal_port['subnet']['cidr'])
                iport_block_pname = \
                    self._get_ippool_name(internal_port['mac_address'])
                ri.ipfilters_manager.add_ippool(iport_block_pname,
                                                [port_subnet])
        # update the new port's pool with other ports' subnet
        ri.ipfilters_manager.add_ippool(block_pname, block_subnets)
        if self.conf.allow_forwarding_between_networks:
            ri.ipfilters_manager.add_ippool(allow_pname, allow_subnets)

        # now setup the IPF rules
        rules = ['block in quick on %s from %s to pool/%d' %
                 (internal_dlname, port_subnet, block_pname)]
        # pass in packets between networks that belong to same tenant
        if self.conf.allow_forwarding_between_networks:
            rules.append('pass in quick on %s from %s to pool/%d' %
                         (internal_dlname, port_subnet, allow_pname))
        # if the external gateway is already setup for the shared router,
        # then we need to add Policy Based Routing (PBR) for this internal
        # network
        ex_gw_port = ri.ex_gw_port
        ex_gw_ip = (ex_gw_port['subnet']['gateway_ip'] if ex_gw_port else None)
        if ex_gw_ip:
            external_dlname = self.get_external_device_name(ex_gw_port['id'])
            rules.append('pass in on %s to %s:%s from any to any' %
                         (internal_dlname, external_dlname, ex_gw_ip))

        ipversion = netaddr.IPNetwork(port_subnet).version
        ri.ipfilters_manager.add_ipf_rules(rules, ipversion)

    def internal_network_removed(self, ri, port):
        internal_dlname = self.get_internal_device_name(port['id'])
        port_subnet = port['subnet']['cidr']
        # remove all the IP filter rules that we added during
        # internal network addition
        block_pname = self._get_ippool_name(port['mac_address'])
        rules = ['block in quick on %s from %s to pool/%d' %
                 (internal_dlname, port_subnet, block_pname)]
        if self.conf.allow_forwarding_between_networks:
            allow_pname = self._get_ippool_name(port['mac_address'], '0')
            rules.append('pass in quick on %s from %s to pool/%d' %
                         (internal_dlname, port_subnet, allow_pname))

        # remove all the IP filter rules that we added during
        # external network addition
        ex_gw_port = ri.ex_gw_port
        ex_gw_ip = (ex_gw_port['subnet']['gateway_ip'] if ex_gw_port else None)
        if ex_gw_ip:
            external_dlname = self.get_external_device_name(ex_gw_port['id'])
            rules.append('pass in on %s to %s:%s from any to any' %
                         (internal_dlname, external_dlname, ex_gw_ip))
        ipversion = netaddr.IPNetwork(port['subnet']['cidr']).version
        ri.ipfilters_manager.remove_ipf_rules(rules, ipversion)

        # remove the ippool
        ri.ipfilters_manager.remove_ippool(block_pname, None)
        if self.conf.allow_forwarding_between_networks:
            ri.ipfilters_manager.remove_ippool(allow_pname, None)

        for internal_port in ri.internal_ports:
            if (self.conf.allow_forwarding_between_networks and
                    internal_port['tenant_id'] == port['tenant_id']):
                iport_allow_pname = \
                    self._get_ippool_name(internal_port['mac_address'], '0')
                ri.ipfilters_manager.remove_ippool(iport_allow_pname,
                                                   [port_subnet])
            else:
                iport_block_pname = \
                    self._get_ippool_name(internal_port['mac_address'])
                ri.ipfilters_manager.remove_ippool(iport_block_pname,
                                                   [port_subnet])

        if net_lib.Datalink.datalink_exists(internal_dlname):
            self.driver.fini_l3(internal_dlname)
            self.driver.unplug(internal_dlname)

    def routers_updated(self, context, routers):
        super(EVSL3NATAgent, self).routers_updated(context, routers)
        if routers:
            # If router's interface was removed, then the VNIC associated
            # with that interface must be deleted immediately. The EVS
            # plugin can delete the virtual port iff the VNIC associated
            # with that virtual port is deleted first.
            self._rpc_loop()

    def routes_updated(self, ri):
        pass
