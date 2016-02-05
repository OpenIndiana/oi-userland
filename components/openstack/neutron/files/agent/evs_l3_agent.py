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

from neutron.agent.l3 import agent as l3_agent
from neutron.agent.l3 import router_info as router
from neutron.agent.linux import utils
from neutron.agent.solaris import interface
from neutron.agent.solaris import ipfilters_manager
from neutron.agent.solaris import net_lib
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
        self.ipfilters_manager = ipfilters_manager.IPfiltersManager()
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
        return net_lib.Datalink.show_vnic()

    def internal_network_added(self, port):
        internal_dlname = self.get_internal_device_name(port['id'])
        # driver just returns if datalink and IP interface already exists
        self.driver.plug(port['tenant_id'], port['network_id'], port['id'],
                         internal_dlname)
        ip_cidrs = common_utils.fixed_ip_cidrs(port['fixed_ips'])
        self.driver.init_l3(internal_dlname, ip_cidrs)

        # Since we support shared router model, we need to block the new
        # internal port from reaching other tenant's ports
        block_pname = self._get_ippool_name(port['mac_address'])
        self.ipfilters_manager.add_ippool(block_pname, None)
        if self.agent_conf.allow_forwarding_between_networks:
            # If allow_forwarding_between_networks is set, then we need to
            # allow forwarding of packets between same tenant's ports.
            allow_pname = self._get_ippool_name(port['mac_address'], '0')
            self.ipfilters_manager.add_ippool(allow_pname, None)

        # walk through the other internal ports and retrieve their
        # cidrs and at the same time add the new internal port's
        # cidr to them
        port_subnet = port['subnets'][0]['cidr']
        block_subnets = []
        allow_subnets = []
        for internal_port in self.internal_ports:
            if internal_port['mac_address'] == port['mac_address']:
                continue
            if (self.agent_conf.allow_forwarding_between_networks and
                    internal_port['tenant_id'] == port['tenant_id']):
                allow_subnets.append(internal_port['subnets'][0]['cidr'])
                # we need to add the port's subnet to this internal_port's
                # allowed_subnet_pool
                iport_allow_pname = \
                    self._get_ippool_name(internal_port['mac_address'], '0')
                self.ipfilters_manager.add_ippool(iport_allow_pname,
                                                  [port_subnet])
            else:
                block_subnets.append(internal_port['subnets'][0]['cidr'])
                iport_block_pname = \
                    self._get_ippool_name(internal_port['mac_address'])
                self.ipfilters_manager.add_ippool(iport_block_pname,
                                                  [port_subnet])
        # update the new port's pool with other ports' subnet
        self.ipfilters_manager.add_ippool(block_pname, block_subnets)
        if self.agent_conf.allow_forwarding_between_networks:
            self.ipfilters_manager.add_ippool(allow_pname, allow_subnets)

        # now setup the IPF rules
        rules = ['block in quick on %s from %s to pool/%d' %
                 (internal_dlname, port_subnet, block_pname)]
        # pass in packets between networks that belong to same tenant
        if self.agent_conf.allow_forwarding_between_networks:
            rules.append('pass in quick on %s from %s to pool/%d' %
                         (internal_dlname, port_subnet, allow_pname))
        # if the external gateway is already setup for the shared router,
        # then we need to add Policy Based Routing (PBR) for this internal
        # network
        ex_gw_port = self.ex_gw_port
        ex_gw_ip = (ex_gw_port['subnets'][0]['gateway_ip']
                    if ex_gw_port else None)
        if ex_gw_ip:
            external_dlname = self.get_external_device_name(ex_gw_port['id'])
            rules.append('pass in on %s to %s:%s from any to !%s' %
                         (internal_dlname, external_dlname, ex_gw_ip,
                          port_subnet))

        ipversion = netaddr.IPNetwork(port_subnet).version
        self.ipfilters_manager.add_ipf_rules(rules, ipversion)
        if self.agent_conf.enable_metadata_proxy and ipversion == 4:
            rdr_rule = ['rdr %s 169.254.169.254/32 port 80 -> %s port %d tcp' %
                        (internal_dlname, port['fixed_ips'][0]['ip_address'],
                         self.agent_conf.metadata_port)]
            self.ipfilters_manager.add_nat_rules(rdr_rule)

    def internal_network_removed(self, port):
        internal_dlname = self.get_internal_device_name(port['id'])
        port_subnet = port['subnets'][0]['cidr']
        # remove all the IP filter rules that we added during
        # internal network addition
        block_pname = self._get_ippool_name(port['mac_address'])
        rules = ['block in quick on %s from %s to pool/%d' %
                 (internal_dlname, port_subnet, block_pname)]
        if self.agent_conf.allow_forwarding_between_networks:
            allow_pname = self._get_ippool_name(port['mac_address'], '0')
            rules.append('pass in quick on %s from %s to pool/%d' %
                         (internal_dlname, port_subnet, allow_pname))

        # remove all the IP filter rules that we added during
        # external network addition
        ex_gw_port = self.ex_gw_port
        ex_gw_ip = (ex_gw_port['subnets'][0]['gateway_ip']
                    if ex_gw_port else None)
        if ex_gw_ip:
            external_dlname = self.get_external_device_name(ex_gw_port['id'])
            rules.append('pass in on %s to %s:%s from any to !%s' %
                         (internal_dlname, external_dlname, ex_gw_ip,
                          port_subnet))
        ipversion = netaddr.IPNetwork(port['subnets'][0]['cidr']).version
        self.ipfilters_manager.remove_ipf_rules(rules, ipversion)

        # remove the ippool
        self.ipfilters_manager.remove_ippool(block_pname, None)
        if self.agent_conf.allow_forwarding_between_networks:
            self.ipfilters_manager.remove_ippool(allow_pname, None)

        for internal_port in self.internal_ports:
            if (self.agent_conf.allow_forwarding_between_networks and
                    internal_port['tenant_id'] == port['tenant_id']):
                iport_allow_pname = \
                    self._get_ippool_name(internal_port['mac_address'], '0')
                self.ipfilters_manager.remove_ippool(iport_allow_pname,
                                                     [port_subnet])
            else:
                iport_block_pname = \
                    self._get_ippool_name(internal_port['mac_address'])
                self.ipfilters_manager.remove_ippool(iport_block_pname,
                                                     [port_subnet])
        if self.agent_conf.enable_metadata_proxy and ipversion == 4:
            rdr_rule = ['rdr %s 169.254.169.254/32 port 80 -> %s port %d tcp' %
                        (internal_dlname, port['fixed_ips'][0]['ip_address'],
                         self.agent_conf.metadata_port)]
            self.ipfilters_manager.remove_nat_rules(rdr_rule)

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

    def _get_ippool_name(self, mac_address, suffix=None):
        # Generate a unique-name for ippool(1m) from that last 3
        # bytes of mac-address. It is called pool name, but it is
        # actually a 32 bit integer
        name = mac_address.split(':')[3:]
        if suffix:
            name.append(suffix)
        return int("".join(name), 16)

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

        existing_nat_rules = [nat_rule for nat_rule in
                              self.ipfilters_manager.ipv4['nat']]
        new_nat_rules = []

        floating_ips = self.get_floating_ips()
        # Loop once to ensure that floating ips are configured.
        for fip in floating_ips:
            fip_ip = fip['floating_ip_address']
            fip_cidr = str(fip_ip) + FLOATING_IP_CIDR_SUFFIX
            new_cidrs.add(fip_cidr)
            fixed_cidr = str(fip['fixed_ip_address']) + '/32'
            nat_rule = 'bimap %s %s -> %s' % (interface_name, fixed_cidr,
                                              fip_cidr)

            if fip_cidr not in existing_cidrs:
                try:
                    ipintf.create_address(fip_cidr)
                    self.ipfilters_manager.add_nat_rules([nat_rule])
                except Exception as err:
                    # TODO(gmoodalb): If we fail in add_nat_rules(), then
                    # we need to remove the fip_cidr address

                    # any exception occurred here should cause the floating IP
                    # to be set in error state
                    fip_statuses[fip['id']] = (
                        l3_constants.FLOATINGIP_STATUS_ERROR)
                    LOG.warn(_("Unable to configure IP address for "
                               "floating IP: %s: %s") % (fip['id'], err))
                    continue
            fip_statuses[fip['id']] = (
                l3_constants.FLOATINGIP_STATUS_ACTIVE)
            LOG.debug("Floating ip %(id)s added, status %(status)s",
                      {'id': fip['id'],
                       'status': fip_statuses.get(fip['id'])})

            new_nat_rules.append(nat_rule)

        # remove all the old NAT rules
        old_nat_rules = list(set(existing_nat_rules) - set(new_nat_rules))
        # Filter out 'bimap' NAT rules as we don't want to remove NAT rules
        # that were added for Metadata server
        old_nat_rules = [rule for rule in old_nat_rules if "bimap" in rule]
        self.ipfilters_manager.remove_nat_rules(old_nat_rules)

        # Clean up addresses that no longer belong on the gateway interface.
        for ip_cidr in existing_cidrs - new_cidrs:
            if ip_cidr.endswith(FLOATING_IP_CIDR_SUFFIX):
                ipintf.delete_address(ip_cidr)
        return fip_statuses

    # Todo(gmoodalb): need to do more work on ipv6 gateway
    def external_gateway_added(self, ex_gw_port, external_dlname):

        if not net_lib.Datalink.datalink_exists(external_dlname):
            dl = net_lib.Datalink(external_dlname)
            # determine the network type of the external network
            evsname = ex_gw_port['network_id']
            cmd = ['/usr/sbin/evsadm', 'show-evs', '-co', 'l2type,vid',
                   '-f', 'evs=%s' % evsname]
            try:
                stdout = utils.execute(cmd)
            except Exception as err:
                LOG.error(_("Failed to retrieve the network type for "
                            "the external network, and it is required "
                            "to create an external gateway port: %s") % err)
                return
            output = stdout.splitlines()[0].strip()
            l2type, vid = output.split(':')
            if l2type != 'flat' and l2type != 'vlan':
                LOG.error(_("External network should be either Flat or "
                            "VLAN based, and it is required to "
                            "create an external gateway port"))
                return
            elif (l2type == 'vlan' and
                  self.agent_conf.get("external_network_datalink", None)):
                LOG.warning(_("external_network_datalink is deprecated in "
                              "Juno and will be removed in the next release "
                              "of Solaris OpenStack. Please use the evsadm "
                              "set-controlprop subcommand to setup the "
                              "uplink-port for an external network"))
                # proceed with the old-style of doing things
                mac_address = ex_gw_port['mac_address']
                dl.create_vnic(self.agent_conf.external_network_datalink,
                               mac_address=mac_address, vid=vid)
            else:
                self.driver.plug(ex_gw_port['tenant_id'],
                                 ex_gw_port['network_id'],
                                 ex_gw_port['id'], external_dlname)

        ip_cidrs = common_utils.fixed_ip_cidrs(ex_gw_port['fixed_ips'])
        self.driver.init_l3(external_dlname, ip_cidrs)

        gw_ip = ex_gw_port['subnets'][0]['gateway_ip']
        if gw_ip:
            cmd = ['/usr/bin/pfexec', '/usr/sbin/route', 'add', 'default',
                   gw_ip]
            stdout = utils.execute(cmd, extra_ok_codes=[errno.EEXIST])
            if 'entry exists' not in stdout:
                self.remove_route = True

            # for each of the internal ports, add Policy Based
            # Routing (PBR) rule
            for port in self.internal_ports:
                internal_dlname = self.get_internal_device_name(port['id'])
                rules = ['pass in on %s to %s:%s from any to !%s' %
                         (internal_dlname, external_dlname, gw_ip,
                          port['subnets'][0]['cidr'])]
                ipversion = \
                    netaddr.IPNetwork(port['subnets'][0]['cidr']).version
                self.ipfilters_manager.add_ipf_rules(rules, ipversion)

    def external_gateway_updated(self, ex_gw_port, external_dlname):
        # There is nothing to do on Solaris
        pass

    def external_gateway_removed(self, ex_gw_port, external_dlname):
        gw_ip = ex_gw_port['subnets'][0]['gateway_ip']
        if gw_ip:
            # remove PBR rules
            for port in self.internal_ports:
                internal_dlname = self.get_internal_device_name(port['id'])
                rules = ['pass in on %s to %s:%s from any to !%s' %
                         (internal_dlname, external_dlname, gw_ip,
                          port['subnets'][0]['cidr'])]
                ipversion = \
                    netaddr.IPNetwork(port['subnets'][0]['cidr']).version
                self.ipfilters_manager.remove_ipf_rules(rules, ipversion)

            if self.remove_route:
                cmd = ['/usr/bin/pfexec', '/usr/sbin/route', 'delete',
                       'default', gw_ip]
                utils.execute(cmd, check_exit_code=False)

        if net_lib.Datalink.datalink_exists(external_dlname):
            self.driver.fini_l3(external_dlname)
            self.driver.unplug(external_dlname)

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

    def external_gateway_snat_rules(self, ex_gw_ip, interface_name):
        rules = []
        ip_cidrs = []
        for port in self.internal_ports:
            if netaddr.IPNetwork(port['subnets'][0]['cidr']).version == 4:
                ip_cidrs.extend(common_utils.fixed_ip_cidrs(port['fixed_ips']))

        for ip_cidr in ip_cidrs:
            rules.append('map %s %s -> %s/32' %
                         (interface_name, ip_cidr, ex_gw_ip))
        return rules

    def _handle_router_snat_rules(self, ex_gw_port, interface_name, action):
        # Remove all the old SNAT rules
        # This is safe because if use_namespaces is set as False
        # then the agent can only configure one router, otherwise
        # each router's SNAT rules will be in their own namespace

        # get only the SNAT rules
        old_snat_rules = [rule for rule in self.ipfilters_manager.ipv4['nat']
                          if rule.startswith('map')]
        self.ipfilters_manager.remove_nat_rules(old_snat_rules)

        # And add them back if the action is add_rules
        if action == 'add_rules' and ex_gw_port:
            # NAT rules are added only if ex_gw_port has an IPv4 address
            for ip_addr in ex_gw_port['fixed_ips']:
                ex_gw_ip = ip_addr['ip_address']
                if netaddr.IPAddress(ex_gw_ip).version == 4:
                    rules = self.external_gateway_snat_rules(ex_gw_ip,
                                                             interface_name)
                    self.ipfilters_manager.add_nat_rules(rules)
                    break

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
