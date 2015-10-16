# vim: tabstop=4 shiftwidth=4 softtabstop=4

# Copyright 2012 VMware, Inc.  All rights reserved.
#
# Copyright (c) 2014, 2015, Oracle and/or its affiliates. All rights reserved.
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

from neutron.agent.common import config
from neutron.agent import l3_agent
from neutron.agent.linux import external_process
from neutron.agent.linux import utils
from neutron.agent.solaris import interface
from neutron.agent.solaris import net_lib
from neutron.agent.solaris import ra
from neutron.common import constants as l3_constants
from neutron.common import utils as common_utils
from neutron.openstack.common import log as logging


LOG = logging.getLogger(__name__)
INTERNAL_DEV_PREFIX = 'l3i'
EXTERNAL_DEV_PREFIX = 'l3e'
FLOATING_IP_CIDR_SUFFIX = '/32'


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

    def _router_added(self, router_id, router):
        ri = l3_agent.RouterInfo(router_id, None,
                                 self.conf.use_namespaces, router)
        self.router_info[router_id] = ri

        if self.conf.enable_metadata_proxy:
            self._spawn_metadata_proxy(ri.router_id, ri.ns_name)

    def _router_removed(self, router_id):
        ri = self.router_info.get(router_id)
        if ri is None:
            LOG.warn(_("Info for router %s were not found. "
                       "Skipping router removal"), router_id)
            return
        ri.router['gw_port'] = None
        ri.router[l3_constants.INTERFACE_KEY] = []
        ri.router[l3_constants.FLOATINGIP_KEY] = []
        self.process_router(ri)
        if self.conf.enable_metadata_proxy:
            self._destroy_metadata_proxy(ri.router_id, ri.ns_name)
        ra.disable_ipv6_ra(ri.router_id)
        del self.router_info[router_id]

    def _get_metadata_proxy_process_manager(self, router_id, ns_name):
        return external_process.ProcessManager(
            self.conf,
            router_id,
            root_helper=None,
            namespace=ns_name)

    def _get_metadata_proxy_callback(self, router_id):
        """Need to override this since we need to pass the absolute
        path to neutron-ns-metadata-proxy binary.
        """
        def callback(pid_file):
            metadata_proxy_socket = cfg.CONF.metadata_proxy_socket
            proxy_cmd = ['/usr/lib/neutron/neutron-ns-metadata-proxy',
                         '--pid_file=%s' % pid_file,
                         '--metadata_proxy_socket=%s' % metadata_proxy_socket,
                         '--router_id=%s' % router_id,
                         '--state_path=%s' % self.conf.state_path,
                         '--metadata_port=%s' % self.conf.metadata_port]
            proxy_cmd.extend(config.get_log_args(
                cfg.CONF, 'neutron-ns-metadata-proxy-%s.log' %
                router_id))
            return proxy_cmd

        return callback

    def external_gateway_snat_rules(self, ex_gw_ip, internal_cidrs,
                                    interface_name):
        rules = []
        for cidr in internal_cidrs:
            rules.append('map %s %s -> %s/32' %
                         (interface_name, cidr, ex_gw_ip))
        return rules

    def _handle_router_snat_rules(self, ri, ex_gw_port, internal_cidrs,
                                  interface_name, action):
        assert not ri.router['distributed']

        # Remove all the old SNAT rules
        # This is safe because if use_namespaces is set as False
        # then the agent can only configure one router, otherwise
        # each router's SNAT rules will be in their own namespace

        # get only the SNAT rules
        old_snat_rules = [rule for rule in ri.ipfilters_manager.ipv4['nat']
                          if rule.startswith('map')]
        ri.ipfilters_manager.remove_nat_rules(old_snat_rules)

        # And add them back if the action is add_rules
        if action == 'add_rules' and ex_gw_port:
            # NAT rules are added only if ex_gw_port has an IPv4 address
            for ip_addr in ex_gw_port['fixed_ips']:
                ex_gw_ip = ip_addr['ip_address']
                if netaddr.IPAddress(ex_gw_ip).version == 4:
                    rules = self.external_gateway_snat_rules(ex_gw_ip,
                                                             internal_cidrs,
                                                             interface_name)
                    ri.ipfilters_manager.add_nat_rules(rules)
                    break

    @common_utils.exception_logger()
    def process_router(self, ri):
        # TODO(mrsmith) - we shouldn't need to check here
        if 'distributed' not in ri.router:
            ri.router['distributed'] = False
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
        new_ipv6_port = False
        old_ipv6_port = False
        for p in new_ports:
            self._set_subnet_info(p)
            self.internal_network_added(ri, p)
            ri.internal_ports.append(p)
            if (not new_ipv6_port and
                    netaddr.IPNetwork(p['subnet']['cidr']).version == 6):
                new_ipv6_port = True

        for p in old_ports:
            self.internal_network_removed(ri, p)
            ri.internal_ports.remove(p)
            if (not old_ipv6_port and
                    netaddr.IPNetwork(p['subnet']['cidr']).version == 6):
                old_ipv6_port = True

        if new_ipv6_port or old_ipv6_port:
            # refresh ndpd daemon after filling in ndpd.conf
            # with the right entries
            ra.enable_ipv6_ra(ri.router_id,
                              internal_ports,
                              self.get_internal_device_name)

        # remove any internal stale router interfaces (i.e., l3i.. VNICs)
        existing_devices = net_lib.Datalink.show_vnic()
        current_internal_devs = set([n for n in existing_devices
                                     if n.startswith(INTERNAL_DEV_PREFIX)])
        current_port_devs = set([self.get_internal_device_name(id) for
                                 id in current_port_ids])
        stale_devs = current_internal_devs - current_port_devs
        for stale_dev in stale_devs:
            LOG.debug(_('Deleting stale internal router device: %s'),
                      stale_dev)
            self.driver.fini_l3(stale_dev)
            self.driver.unplug(stale_dev)

        # TODO(salv-orlando): RouterInfo would be a better place for
        # this logic too
        ex_gw_port_id = (ex_gw_port and ex_gw_port['id'] or
                         ri.ex_gw_port and ri.ex_gw_port['id'])

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

            self._set_subnet_info(ex_gw_port)
            if not ri.ex_gw_port:
                self.external_gateway_added(ri, ex_gw_port, interface_name)
            elif not _gateway_ports_equal(ex_gw_port, ri.ex_gw_port):
                self.external_gateway_updated(ri, ex_gw_port, interface_name)
        elif not ex_gw_port and ri.ex_gw_port:
            self.external_gateway_removed(ri, ri.ex_gw_port, interface_name)

        # Remove any external stale router interfaces (i.e., l3e.. VNICs)
        stale_devs = [dev for dev in existing_devices
                      if dev.startswith(EXTERNAL_DEV_PREFIX)
                      and dev != interface_name]
        for stale_dev in stale_devs:
            LOG.debug(_('Deleting stale external router device: %s'),
                      stale_dev)
            self.driver.fini_l3(stale_dev)
            self.driver.unplug(stale_dev)

        # Process static routes for router
        self.routes_updated(ri)

        # Process SNAT rules for external gateway
        if (not ri.router['distributed'] or
                ex_gw_port and self.get_gw_port_host(ri.router) == self.host):
            # Get IPv4 only internal CIDRs
            internal_cidrs = [p['ip_cidr'] for p in ri.internal_ports
                              if netaddr.IPNetwork(p['ip_cidr']).version == 4]
            ri.perform_snat_action(self._handle_router_snat_rules,
                                   internal_cidrs, interface_name)

        # Process SNAT/DNAT rules for floating IPs
        fip_statuses = {}
        if ex_gw_port:
            existing_floating_ips = ri.floating_ips
            fip_statuses = self.process_router_floating_ips(ri, ex_gw_port)
            # Identify floating IPs which were disabled
            ri.floating_ips = set(fip_statuses.keys())
            for fip_id in existing_floating_ips - ri.floating_ips:
                fip_statuses[fip_id] = l3_constants.FLOATINGIP_STATUS_DOWN
            # Update floating IP status on the neutron server
            self.plugin_rpc.update_floatingip_statuses(
                self.context, ri.router_id, fip_statuses)

        # Update ex_gw_port and enable_snat on the router info cache
        ri.ex_gw_port = ex_gw_port
        ri.enable_snat = ri.router.get('enable_snat')

    def process_router_floating_ips(self, ri, ex_gw_port):
        """Configure the router's floating IPs
        Configures floating ips using ipnat(1m) on the router's gateway device.

        Cleans up floating ips that should not longer be configured.
        """
        ifname = self.get_external_device_name(ex_gw_port['id'])
        ipintf = net_lib.IPInterface(ifname)
        ipaddr_list = ipintf.ipaddr_list()['static']

        existing_cidrs = set(ipaddr_list)
        new_cidrs = set()

        existing_nat_rules = [nat_rule for nat_rule in
                              ri.ipfilters_manager.ipv4['nat']]
        new_nat_rules = []

        # Loop once to ensure that floating ips are configured.
        fip_statuses = {}
        for fip in ri.router.get(l3_constants.FLOATINGIP_KEY, []):
            fip_ip = fip['floating_ip_address']
            fip_cidr = str(fip_ip) + FLOATING_IP_CIDR_SUFFIX
            new_cidrs.add(fip_cidr)
            fixed_cidr = str(fip['fixed_ip_address']) + '/32'
            nat_rule = 'bimap %s %s -> %s' % (ifname, fixed_cidr, fip_cidr)

            if fip_cidr not in existing_cidrs:
                try:
                    ipintf.create_address(fip_cidr)
                    ri.ipfilters_manager.add_nat_rules([nat_rule])
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
            new_nat_rules.append(nat_rule)

        # remove all the old NAT rules
        old_nat_rules = list(set(existing_nat_rules) - set(new_nat_rules))
        # Filter out 'bimap' NAT rules as we don't want to remove NAT rules
        # that were added for Metadata server
        old_nat_rules = [rule for rule in old_nat_rules if "bimap" in rule]
        ri.ipfilters_manager.remove_nat_rules(old_nat_rules)

        # Clean up addresses that no longer belong on the gateway interface.
        for ip_cidr in existing_cidrs - new_cidrs:
            if ip_cidr.endswith(FLOATING_IP_CIDR_SUFFIX):
                ipintf.delete_address(ip_cidr)
        return fip_statuses

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

    def external_gateway_added(self, ri, ex_gw_port, external_dlname):

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
                  self.conf.get("external_network_datalink", None)):
                LOG.warning(_("external_network_datalink is deprecated in "
                              "Juno and will be removed in the next release "
                              "of Solaris OpenStack. Please use the evsadm "
                              "set-controlprop subcommand to setup the "
                              "uplink-port for an external network"))
                # proceed with the old-style of doing things
                mac_address = ex_gw_port['mac_address']
                dl.create_vnic(self.conf.external_network_datalink,
                               mac_address=mac_address, vid=vid)
            else:
                self.driver.plug(ex_gw_port['tenant_id'],
                                 ex_gw_port['network_id'],
                                 ex_gw_port['id'], external_dlname)

        self.driver.init_l3(external_dlname, [ex_gw_port['ip_cidr']])

        # TODO(gmoodalb): wrap route(1m) command within a class in net_lib.py
        gw_ip = ex_gw_port['subnet']['gateway_ip']
        if gw_ip:
            cmd = ['/usr/bin/pfexec', '/usr/sbin/route', 'add', 'default',
                   gw_ip]
            stdout = utils.execute(cmd, extra_ok_codes=[errno.EEXIST])
            ri.remove_route = True
            if 'entry exists' in stdout:
                ri.remove_route = False

            # for each of the internal ports, add Policy Based
            # Routing (PBR) rule
            for port in ri.internal_ports:
                internal_dlname = self.get_internal_device_name(port['id'])
                rules = ['pass in on %s to %s:%s from any to !%s' %
                         (internal_dlname, external_dlname, gw_ip,
                          port['subnet']['cidr'])]
                ipversion = netaddr.IPNetwork(port['subnet']['cidr']).version
                ri.ipfilters_manager.add_ipf_rules(rules, ipversion)

    def external_gateway_updated(self, ri, ex_gw_port, external_dlname):
        # There is nothing to do on Solaris
        pass

    def external_gateway_removed(self, ri, ex_gw_port, external_dlname):
        gw_ip = ex_gw_port['subnet']['gateway_ip']
        if gw_ip:
            # remove PBR rules
            for port in ri.internal_ports:
                internal_dlname = self.get_internal_device_name(port['id'])
                rules = ['pass in on %s to %s:%s from any to !%s' %
                         (internal_dlname, external_dlname, gw_ip,
                          port['subnet']['cidr'])]
                ipversion = netaddr.IPNetwork(port['subnet']['cidr']).version
                ri.ipfilters_manager.remove_ipf_rules(rules, ipversion)

            if ri.remove_route:
                cmd = ['/usr/bin/pfexec', '/usr/sbin/route', 'delete',
                       'default', gw_ip]
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
            rules.append('pass in on %s to %s:%s from any to !%s' %
                         (internal_dlname, external_dlname, ex_gw_ip,
                          port_subnet))

        ipversion = netaddr.IPNetwork(port_subnet).version
        ri.ipfilters_manager.add_ipf_rules(rules, ipversion)

        # if metadata proxy is enabled, then add the necessary
        # IP NAT rules to forward the metadata requests to the
        # metadata proxy server
        if self.conf.enable_metadata_proxy and ipversion == 4:
            # TODO(gmoodalb): when IP Filter allows redirection of packets
            # to loopback IP address, then we need to add an IPF rule allowing
            # only packets destined to 127.0.0.1:9697 to
            # neutron-ns-metadata-proxy server
            rules = ['rdr %s 169.254.169.254/32 port 80 -> %s port %d tcp' %
                     (internal_dlname, port['fixed_ips'][0]['ip_address'],
                      self.conf.metadata_port)]
            ri.ipfilters_manager.add_nat_rules(rules)

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
            rules.append('pass in on %s to %s:%s from any to !%s' %
                         (internal_dlname, external_dlname, ex_gw_ip,
                          port_subnet))
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

        # if metadata proxy is enabled, then remove the IP NAT rules that
        # were added while adding the internal network
        if self.conf.enable_metadata_proxy and ipversion == 4:
            rules = ['rdr %s 169.254.169.254/32 port 80 -> %s port %d tcp' %
                     (internal_dlname, port['fixed_ips'][0]['ip_address'],
                      self.conf.metadata_port)]
            ri.ipfilters_manager.remove_nat_rules(rules)

        if net_lib.Datalink.datalink_exists(internal_dlname):
            self.driver.fini_l3(internal_dlname)
            self.driver.unplug(internal_dlname)

    def routes_updated(self, ri):
        pass
