# vim: tabstop=4 shiftwidth=4 softtabstop=4

# Copyright 2012 VMware, Inc.  All rights reserved.
#
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

"""
Based off generic l3_agent (neutron/agent/l3_agent) code
"""

import errno
import netaddr

from oslo.config import cfg
from oslo_log import log as logging

from neutron.agent.common import ovs_lib
from neutron.agent.l3 import agent as l3_agent
from neutron.agent.l3 import router_info as router
from neutron.agent.linux import utils
from neutron.agent.solaris import interface
from neutron.agent.solaris import net_lib
from neutron.agent.solaris import packetfilter
from neutron.agent.solaris import ra
from neutron.callbacks import events
from neutron.callbacks import registry
from neutron.callbacks import resources
from neutron.common import constants as l3_constants
from neutron.common import exceptions as n_exc
from neutron.common import utils as common_utils
from oslo_utils import importutils
from oslo_log import log as logging

import neutron_vpnaas.services.vpn.agent as neutron_vpnaas
from neutron_vpnaas.extensions import vpnaas
from neutron_vpnaas.services.vpn import vpn_service

LOG = logging.getLogger(__name__)
INTERNAL_DEV_PREFIX = 'l3i'
EXTERNAL_DEV_PREFIX = 'l3e'
FLOATING_IP_CIDR_SUFFIX = '/32'


class SolarisRouterInfo(router.RouterInfo):

    def __init__(self, router_id, router, agent_conf, interface_driver,
                 use_ipv6=False):
        super(SolarisRouterInfo, self).__init__(router_id, router, agent_conf,
                                                interface_driver, use_ipv6)
        self.pf = packetfilter.PacketFilter("_auto/neutron:l3:agent")
        self.iptables_manager = None
        self.remove_route = False

    def initialize(self, process_monitor):
        """Initialize the router on the system.

        This differs from __init__ in that this method actually affects the
        system creating namespaces, starting processes, etc.  The other merely
        initializes the python object.  This separates in-memory object
        initialization from methods that actually go do stuff to the system.

        :param process_monitor: The agent's process monitor instance.
        """
        self.process_monitor = process_monitor
        self.radvd = ra.NDPD(self.router_id, self.get_internal_device_name)

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

    def routes_updated(self):
        pass

    def _get_existing_devices(self):
        return net_lib.Datalink.show_link()

    def internal_network_added(self, port):
        internal_dlname = self.get_internal_device_name(port['id'])
        # driver just returns if datalink and IP interface already exists
        self.driver.plug(port['tenant_id'], port['network_id'], port['id'],
                         internal_dlname, port['mac_address'],
                         vif_type=port.get('binding:vif_type'))
        fixed_ips = port['fixed_ips']
        ip_cidrs = common_utils.fixed_ip_cidrs(fixed_ips)
        self.driver.init_l3(internal_dlname, ip_cidrs)
        for fixed_ip in fixed_ips:
            net_lib.send_ip_addr_adv_notif(internal_dlname,
                                           fixed_ip['ip_address'],
                                           self.agent_conf)

        # Since we support shared router model, we need to block the new
        # internal port from reaching other tenant's ports. However, if
        # allow_forwarding_between_networks is set, then we need to
        # allow forwarding of packets between same tenant's ports.

        # walk through the other internal ports and retrieve their
        # cidrs and at the same time add the new internal port's
        # cidr to them
        port_subnet = port['subnets'][0]['cidr']
        block_subnets = []
        allow_subnets = []
        for internal_port in self.internal_ports:
            # skip the port being added
            if internal_port['mac_address'] == port['mac_address']:
                continue
            internal_port_dlname = \
                self.get_internal_device_name(internal_port['id'])
            if (self.agent_conf.allow_forwarding_between_networks and
                    internal_port['tenant_id'] == port['tenant_id']):
                allow_subnets.append(internal_port['subnets'][0]['cidr'])
                # we need to add the port's subnet to this internal_port's
                # allowed_subnet_table
                iport_allow_tblname = 'allow_' + internal_port_dlname
                self.pf.add_table_entry(iport_allow_tblname, [port_subnet],
                                        [internal_port_dlname, 'normal'])
            else:
                block_subnets.append(internal_port['subnets'][0]['cidr'])
                iport_block_tblname = 'block_' + internal_port_dlname
                self.pf.add_table_entry(iport_block_tblname, [port_subnet],
                                        [internal_port_dlname, 'normal'])

        # update the new port's table with other ports' subnet
        block_tblname = 'block_' + internal_dlname
        self.pf.add_table_entry(block_tblname, block_subnets,
                                [internal_dlname, 'normal'])
        if self.agent_conf.allow_forwarding_between_networks:
            allow_tblname = 'allow_' + internal_dlname
            self.pf.add_table_entry(allow_tblname, allow_subnets,
                                    [internal_dlname, 'normal'])

        # now setup the PF rules
        label = 'block_%s' % internal_dlname
        rules = ['block in quick from %s to <%s> label %s' %
                 (port_subnet, block_tblname, label)]
        # pass in packets between networks that belong to same tenant
        if self.agent_conf.allow_forwarding_between_networks:
            label = 'allow_%s' % internal_dlname
            rules.append('pass in quick from %s to <%s> label %s' %
                         (port_subnet, allow_tblname, label))

        # if metadata is enabled, then we need to redirect all the packets
        # arriving at 169.254.169.254:80 to neutron-metadata-proxy server
        # listening at self.agent_conf.metadata_port
        ipversion = netaddr.IPNetwork(port_subnet).version
        if self.agent_conf.enable_metadata_proxy and ipversion == 4:
            fixed_ip_address = port['fixed_ips'][0]['ip_address']
            label = 'metadata_%s' % fixed_ip_address
            rules.append('pass in quick proto tcp to 169.254.169.254/32 '
                         'port 80 rdr-to %s port %s label %s' %
                         (fixed_ip_address, self.agent_conf.metadata_port,
                          label))
        # finally add all the rules in one shot
        anchor_option = "on %s" % internal_dlname
        self.pf.add_nested_anchor_rule(None, internal_dlname, anchor_option)
        self.pf.add_rules(rules, [internal_dlname, 'normal'])

        ex_gw_port = self.ex_gw_port
        if not ex_gw_port:
            return

        ex_gw_ip = ex_gw_port['subnets'][0]['gateway_ip']
        if not ex_gw_ip:
            return

        if netaddr.IPAddress(ex_gw_ip).version != 4 or ipversion != 4:
            return

        # if the external gateway is already setup for the shared router,
        # then we need to add Policy Based Routing (PBR) for this internal
        # network
        external_dlname = self.get_external_device_name(ex_gw_port['id'])
        label = 'pbr_%s' % port_subnet.replace('/', '_')
        # don't forward broadcast packets out of the internal subnet
        pbr_rules = ['pass in quick to 255.255.255.255 label %s_bcast' %
                     label]
        pbr_rules.append('pass in to !%s route-to {(%s %s)} label %s' %
                         (port_subnet, external_dlname, ex_gw_ip, label))

        self.pf.add_rules(pbr_rules, [internal_dlname, 'pbr'])
        if self._snat_enabled:
            ex_gw_ip_cidrs = \
                common_utils.fixed_ip_cidrs(ex_gw_port['fixed_ips'])
            snat_rule = 'pass out from %s to any nat-to %s' % \
                (ip_cidrs[0], ex_gw_ip_cidrs[0])
            self.pf.add_rules([snat_rule],
                              [external_dlname, '%s' % internal_dlname])

    def internal_network_removed(self, port):
        internal_dlname = self.get_internal_device_name(port['id'])
        port_subnet = port['subnets'][0]['cidr']

        for internal_port in self.internal_ports:
            internal_port_dlname = \
                self.get_internal_device_name(internal_port['id'])
            if (self.agent_conf.allow_forwarding_between_networks and
                    internal_port['tenant_id'] == port['tenant_id']):
                iport_allow_tblname = 'allow_' + internal_port_dlname
                self.pf.remove_table_entry(iport_allow_tblname, [port_subnet],
                                           [internal_port_dlname, 'normal'])
            else:
                iport_block_tblname = 'block_' + internal_port_dlname
                self.pf.remove_table_entry(iport_block_tblname, [port_subnet],
                                           [internal_port_dlname, 'normal'])

        # remove the nested anchors rule from neutron:l3:agent
        self.pf.remove_nested_anchor_rule(None, internal_dlname)

        # remove the anchor and tables associated with this internal port
        self.pf.remove_anchor_recursively([internal_dlname])

        if net_lib.Datalink.datalink_exists(internal_dlname):
            self.driver.fini_l3(internal_dlname)
            self.driver.unplug(internal_dlname)

    def _process_internal_ports(self):
        existing_port_ids = set([p['id'] for p in self.internal_ports])

        internal_ports = self.router.get(l3_constants.INTERFACE_KEY, [])
        current_port_ids = set([p['id'] for p in internal_ports
                                if p['admin_state_up']])

        new_port_ids = current_port_ids - existing_port_ids
        new_ports = [p for p in internal_ports if p['id'] in new_port_ids]
        old_ports = [p for p in self.internal_ports if
                     p['id'] not in current_port_ids]
#         updated_ports = self._get_updated_ports(self.internal_ports,
#                                                 internal_ports)

        enable_ra = False
        for p in new_ports:
            self.internal_network_added(p)
            self.internal_ports.append(p)
            enable_ra = enable_ra or self._port_has_ipv6_subnet(p)

        for p in old_ports:
            self.internal_network_removed(p)
            self.internal_ports.remove(p)
            enable_ra = enable_ra or self._port_has_ipv6_subnet(p)

#         if updated_ports:
#             for index, p in enumerate(internal_ports):
#                 if not updated_ports.get(p['id']):
#                     continue
#                 self.internal_ports[index] = updated_ports[p['id']]
#                 interface_name = self.get_internal_device_name(p['id'])
#                 ip_cidrs = common_utils.fixed_ip_cidrs(p['fixed_ips'])
#                 self.driver.init_l3(interface_name, ip_cidrs=ip_cidrs,
#                         namespace=self.ns_name)
#                 enable_ra = enable_ra or self._port_has_ipv6_subnet(p)

        # Enable RA
        if enable_ra:
            self.radvd.enable(internal_ports)

        # remove any internal stale router interfaces (i.e., l3i.. VNICs)
        existing_devices = self._get_existing_devices()
        current_internal_devs = set(n for n in existing_devices
                                    if n.startswith(INTERNAL_DEV_PREFIX))
        current_port_devs = set(self.get_internal_device_name(port_id)
                                for port_id in current_port_ids)
        stale_devs = current_internal_devs - current_port_devs
        for stale_dev in stale_devs:
            LOG.debug(_('Deleting stale internal router device: %s'),
                      stale_dev)
            self.driver.fini_l3(stale_dev)
            self.driver.unplug(stale_dev)

    def process_floating_ip_addresses(self, interface_name):
        """Configure IP addresses on router's external gateway interface.

        Ensures addresses for existing floating IPs and cleans up
        those that should not longer be configured.
        """

        fip_statuses = {}
        if interface_name is None:
            LOG.debug('No Interface for floating IPs router: %s',
                      self.router['id'])
            return fip_statuses

        ipintf = net_lib.IPInterface(interface_name)
        ipaddr_list = ipintf.ipaddr_list()['static']

        existing_cidrs = set(ipaddr_list)
        new_cidrs = set()

        floating_ips = self.get_floating_ips()
        # Loop once to ensure that floating ips are configured.
        for fip in floating_ips:
            fip_ip = fip['floating_ip_address']
            fip_cidr = str(fip_ip) + FLOATING_IP_CIDR_SUFFIX
            new_cidrs.add(fip_cidr)
            fixed_cidr = str(fip['fixed_ip_address']) + '/32'
            label = 'fip_%s' % fip_cidr.replace('/', '_')
            binat_rule = 'pass quick from %s to any binat-to %s label %s' % \
                (fixed_cidr, fip_cidr, label)

            if fip_cidr not in existing_cidrs:
                try:
                    ipintf.create_address(fip_cidr)
                    self.pf.add_rules([binat_rule], [interface_name,
                                                     fip_cidr.split('/')[0]])
                    net_lib.send_ip_addr_adv_notif(interface_name,
                                                   fip['floating_ip_address'],
                                                   self.agent_conf)
                except Exception as err:
                    # any exception occurred here should cause the floating IP
                    # to be set in error state
                    fip_statuses[fip['id']] = (
                        l3_constants.FLOATINGIP_STATUS_ERROR)
                    LOG.warn(_("Unable to configure IP address for "
                               "floating IP: %s: %s") % (fip['id'], err))
                    # remove the fip_cidr address if it was added
                    try:
                        ipintf.delete_address(fip_cidr)
                    except:
                        pass
                    continue
            fip_statuses[fip['id']] = (
                l3_constants.FLOATINGIP_STATUS_ACTIVE)

            LOG.debug("Floating ip %(id)s added, status %(status)s",
                      {'id': fip['id'],
                       'status': fip_statuses.get(fip['id'])})

        # Clean up addresses that no longer belong on the gateway interface and
        # remove the binat-to PF rule associated with them
        for ip_cidr in existing_cidrs - new_cidrs:
            if ip_cidr.endswith(FLOATING_IP_CIDR_SUFFIX):
                self.pf.remove_anchor([interface_name, ip_cidr.split('/')[0]])
                ipintf.delete_address(ip_cidr)
        return fip_statuses

    # TODO(gmoodalb): need to do more work on ipv6 gateway
    def external_gateway_added(self, ex_gw_port, external_dlname):
        self.driver.plug(ex_gw_port['tenant_id'], ex_gw_port['network_id'],
                         ex_gw_port['id'], external_dlname,
                         ex_gw_port['mac_address'],
                         bridge=self.agent_conf.external_network_bridge,
                         vif_type=ex_gw_port.get('binding:vif_type'))
        ip_cidrs = common_utils.fixed_ip_cidrs(ex_gw_port['fixed_ips'])
        self.driver.init_l3(external_dlname, ip_cidrs)
        for fixed_ip in ex_gw_port['fixed_ips']:
            net_lib.send_ip_addr_adv_notif(external_dlname,
                                           fixed_ip['ip_address'],
                                           self.agent_conf)

        # add nested anchor rule first
        anchor_option = "on %s" % external_dlname
        self.pf.add_nested_anchor_rule(None, external_dlname, anchor_option)

        gw_ip = ex_gw_port['subnets'][0]['gateway_ip']
        if gw_ip:
            cmd = ['/usr/bin/pfexec', '/usr/sbin/route', 'add', 'default',
                   gw_ip]
            stdout = utils.execute(cmd, extra_ok_codes=[errno.EEXIST])
            if 'entry exists' not in stdout:
                self.remove_route = True

            # for each of the internal ports, add Policy Based Routing (PBR)
            # rule iff ex_gw_ip is IPv4 and the internal port is IPv4
            if netaddr.IPAddress(gw_ip).version != 4:
                return
            for port in self.internal_ports:
                port_subnet = port['subnets'][0]['cidr']
                if netaddr.IPNetwork(port_subnet).version != 4:
                    continue
                internal_dlname = self.get_internal_device_name(port['id'])
                label = 'pbr_%s' % port_subnet.replace('/', '_')
                pbr_rules = ['pass in quick to 255.255.255.255 '
                             'label %s_bcast' % label]
                pbr_rules.append('pass in to !%s route-to {(%s %s)} '
                                 'label %s' % (port_subnet, external_dlname,
                                               gw_ip, label))
                self.pf.add_rules(pbr_rules, [internal_dlname, 'pbr'])

    def external_gateway_updated(self, ex_gw_port, external_dlname):
        # There is nothing to do on Solaris
        pass

    def external_gateway_removed(self, ex_gw_port, external_dlname):
        # remove nested anchor rule first
        self.pf.remove_nested_anchor_rule(None, external_dlname)

        gw_ip = ex_gw_port['subnets'][0]['gateway_ip']
        if gw_ip:
            # remove PBR rules
            for port in self.internal_ports:
                internal_dlname = self.get_internal_device_name(port['id'])
                self.pf.remove_anchor([internal_dlname, 'pbr'])

            if self.remove_route:
                cmd = ['/usr/bin/pfexec', '/usr/sbin/route', 'delete',
                       'default', gw_ip]
                utils.execute(cmd, check_exit_code=False)

        if net_lib.Datalink.datalink_exists(external_dlname):
            self.driver.fini_l3(external_dlname)
            self.driver.unplug(external_dlname,
                               self.agent_conf.external_network_bridge)

    def _process_external_gateway(self, ex_gw_port):
        # TODO(Carl) Refactor to clarify roles of ex_gw_port vs self.ex_gw_port
        ex_gw_port_id = (ex_gw_port and ex_gw_port['id'] or
                         self.ex_gw_port and self.ex_gw_port['id'])

        interface_name = None
        if ex_gw_port_id:
            interface_name = self.get_external_device_name(ex_gw_port_id)
        if ex_gw_port:
            def _gateway_ports_equal(port1, port2):
                def _get_filtered_dict(d, ignore):
                    return dict((k, v) for k, v in d.iteritems()
                                if k not in ignore)

                keys_to_ignore = set(['binding:host_id'])
                port1_filtered = _get_filtered_dict(port1, keys_to_ignore)
                port2_filtered = _get_filtered_dict(port2, keys_to_ignore)
                return port1_filtered == port2_filtered

            if not self.ex_gw_port:
                self.external_gateway_added(ex_gw_port, interface_name)
            elif not _gateway_ports_equal(ex_gw_port, self.ex_gw_port):
                self.external_gateway_updated(ex_gw_port, interface_name)
        elif not ex_gw_port and self.ex_gw_port:
            self.external_gateway_removed(self.ex_gw_port, interface_name)

        # Remove any external stale router interfaces (i.e., l3e.. VNICs)
        existing_devices = self._get_existing_devices()
        stale_devs = [dev for dev in existing_devices
                      if dev.startswith(EXTERNAL_DEV_PREFIX) and
                      dev != interface_name]
        for stale_dev in stale_devs:
            LOG.debug(_('Deleting stale external router device: %s'),
                      stale_dev)
            self.driver.fini_l3(stale_dev)
            self.driver.unplug(stale_dev)

        # Process SNAT rules for external gateway
        self.perform_snat_action(self._handle_router_snat_rules,
                                 interface_name)

    def external_gateway_snat_rules(self, ex_gw_ip, external_dlname):
        rules = {}
        for port in self.internal_ports:
            if netaddr.IPNetwork(port['subnets'][0]['cidr']).version == 4:
                ip_cidrs = common_utils.fixed_ip_cidrs(port['fixed_ips'])
                label = 'snat_%s' % ip_cidrs[0].replace('/', '_')
                rule = 'pass out from %s to any nat-to %s label %s' % \
                    (ip_cidrs[0], ex_gw_ip, label)
                rules[port['id']] = [rule]

        return rules

    def _handle_router_snat_rules(self, ex_gw_port, external_dlname, action):
        # Remove all the old SNAT rules
        # This is safe because if use_namespaces is set as False
        # then the agent can only configure one router, otherwise
        # each router's SNAT rules will be in their own namespace

        for port in self.internal_ports:
            internal_dlname = self.get_internal_device_name(port['id'])
            self.pf.remove_anchor([external_dlname, internal_dlname])

        # And add them back if the action is add_rules
        if action == 'add_rules' and ex_gw_port:
            # NAT rules are added only if ex_gw_port has an IPv4 address
            for ip_addr in ex_gw_port['fixed_ips']:
                ex_gw_ip = ip_addr['ip_address']
                if netaddr.IPAddress(ex_gw_ip).version == 4:
                    rules = self.external_gateway_snat_rules(ex_gw_ip,
                                                             external_dlname)
                    if not rules:
                        continue
                    for port_id, rule in rules.iteritems():
                        internal_dlname = \
                            self.get_internal_device_name(port_id)
                        self.pf.add_rules(rule, [external_dlname,
                                                 internal_dlname])

    def process_external(self, agent):
        existing_floating_ips = self.floating_ips
        try:
            ex_gw_port = self.get_ex_gw_port()
            self._process_external_gateway(ex_gw_port)
            # TODO(Carl) Return after setting existing_floating_ips and
            # still call update_fip_statuses?
            if not ex_gw_port:
                return

            # Once NAT rules for floating IPs are safely in place
            # configure their addresses on the external gateway port
            interface_name = self.get_external_device_name(ex_gw_port['id'])
            fip_statuses = self.configure_fip_addresses(interface_name)
        except (n_exc.FloatingIpSetupException,
                n_exc.IpTablesApplyException) as e:
                # All floating IPs must be put in error state
                LOG.exception(e)
                fip_statuses = self.put_fips_in_error_state()

        agent.update_fip_statuses(self, existing_floating_ips, fip_statuses)


class EVSL3NATAgent(l3_agent.L3NATAgentWithStateReport):
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
        cfg.CONF.register_opts(neutron_vpnaas.vpn_agent_opts, 'vpnagent')
        self.service = vpn_service.VPNService(self)
        self.device_drivers = self.service.load_device_drivers(host)

    def _router_added(self, router_id, router):
        args = []
        kwargs = {
            'router_id': router_id,
            'router': router,
            'use_ipv6': self.use_ipv6,
            'agent_conf': self.conf,
            'interface_driver': self.driver,
        }
        ri = SolarisRouterInfo(*args, **kwargs)
        registry.notify(resources.ROUTER, events.BEFORE_CREATE,
                        self, router=ri)

        self.router_info[router_id] = ri

        ri.initialize(self.process_monitor)

    def _process_router_if_compatible(self, router):
        if (self.conf.external_network_bridge and not ovs_lib.BaseOVS().
                bridge_exists(self.conf.external_network_bridge)):
            LOG.error(_("The external network bridge '%s' does not exist"),
                      self.conf.external_network_bridge)
            return

        # If namespaces are disabled, only process the router associated
        # with the configured agent id.
        if (not self.conf.use_namespaces and
                router['id'] != self.conf.router_id):
            raise n_exc.RouterNotCompatibleWithAgent(router_id=router['id'])

        # Either ex_net_id or handle_internal_only_routers must be set
        ex_net_id = (router['external_gateway_info'] or {}).get('network_id')
        if not ex_net_id and not self.conf.handle_internal_only_routers:
            raise n_exc.RouterNotCompatibleWithAgent(router_id=router['id'])

        # If target_ex_net_id and ex_net_id are set they must be equal
        target_ex_net_id = self._fetch_external_net_id()
        if (target_ex_net_id and ex_net_id and ex_net_id != target_ex_net_id):
            # Double check that our single external_net_id has not changed
            # by forcing a check by RPC.
            if ex_net_id != self._fetch_external_net_id(force=True):
                raise n_exc.RouterNotCompatibleWithAgent(
                    router_id=router['id'])

        if router['id'] not in self.router_info:
            self._process_added_router(router)
        else:
            self._process_updated_router(router)
