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
Based off of generic l3_agent (neutron/agent/l3/agent.py) code
"""

import errno
import netaddr

from oslo_config import cfg
from oslo_log import log as logging

from neutron._i18n import _, _LE, _LW
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
from neutron.common import ipv6_utils
from neutron.common import utils as common_utils

from neutron_vpnaas.services.vpn import vpn_service
import neutron_vpnaas.services.vpn.agent as neutron_vpnaas

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
        self.router_namespace = None
        self.ns_name = None
        self.ipnet_gwportname = dict()
        self.tenant_subnets = dict()
        self.tenant_subnets['all_tenants'] = set()

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

    def update_routing_table(self, operation, route):
        if operation == 'replace':
            operation = 'change'
            cmd = ['/usr/sbin/route', 'get', route['destination']]
            try:
                utils.execute(cmd, log_fail_as_error=False)
            except:
                operation = 'add'
            cmd = ['/usr/sbin/route', operation, route['destination'],
                   route['nexthop']]
            utils.execute(cmd)
        else:
            assert operation == 'delete'
            cmd = ['/usr/sbin/route', 'delete', route['destination'],
                   route['nexthop']]
            utils.execute(cmd)

    def _add_floating_ip_rules(self, interface_name, fip, fip_statuses):
        fixed_ip = fip['fixed_ip_address']
        fip_ip = fip['floating_ip_address']
        for ipnet, gwportname in self.ipnet_gwportname.iteritems():
            if fixed_ip in ipnet:
                break
        else:
            fip_statuses[fip['id']] = l3_constants.FLOATINGIP_STATUS_ERROR
            LOG.warn(_("Unable to configure IP address for floating IP(%s)"
                       " '%s' for '%s'") % (fip['id'], fip_ip, fixed_ip))
            return False

        label = 'fip_%s' % str(fip_ip)
        fip_rules = ['pass out quick from %s to any nat-to %s static-port '
                     'label %s_out reply-to %s@%s' % (fixed_ip, fip_ip, label,
                                                      fixed_ip,  gwportname)]
        fip_rules.append('pass in quick from any to %s rdr-to %s label %s_in '
                         'route-to %s@%s' % (fip_ip, fixed_ip, label,
                                             fixed_ip, gwportname))
        self.pf.add_rules(fip_rules, [interface_name, fip_ip])
        return True

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
            fixed_ip = fip['fixed_ip_address']
            fip_ip = fip['floating_ip_address']
            fip_cidr = str(fip_ip) + FLOATING_IP_CIDR_SUFFIX
            new_cidrs.add(fip_cidr)
            fip_statuses[fip['id']] = l3_constants.FLOATINGIP_STATUS_ACTIVE
            if fip_cidr not in existing_cidrs:
                try:
                    ipintf.create_address(fip_cidr, ifcheck=False,
                                          addrcheck=False)
                    if not self._add_floating_ip_rules(interface_name, fip,
                                                       fip_statuses):
                        continue
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
            else:
                existing_anchor_rules = self.pf.list_anchor_rules(
                    [interface_name, fip_ip])
                # check if existing fip has been reassigned
                fip_reassigned = any([fixed_ip not in rule for rule in
                                      existing_anchor_rules])
                if fip_reassigned:
                    LOG.debug("Floating ip '%s' reassigned to '%s'",
                              fip_ip, fixed_ip)
                    # flush rules associated with old fixed_ip and add
                    # new rules for the new fixed_ip
                    self.pf.remove_anchor([interface_name, fip_ip])
                    if not self._add_floating_ip_rules(interface_name, fip,
                                                       fip_statuses):
                        continue
                elif fip_statuses[fip['id']] == fip['status']:
                    # mark the status as not changed. we can't remove it
                    # because that's how the caller determines that it was
                    # removed (TODO(gmoodalb): check this)
                    fip_statuses[fip['id']] = router.FLOATINGIP_STATUS_NOCHANGE

            LOG.debug("Floating ip %(id)s added, status %(status)s",
                      {'id': fip['id'],
                       'status': fip_statuses.get(fip['id'])})

        # Clean up addresses that no longer belong on the gateway interface and
        # remove the binat-to PF rule associated with them
        for ip_cidr in existing_cidrs - new_cidrs:
            if ip_cidr.endswith(FLOATING_IP_CIDR_SUFFIX):
                LOG.debug("Removing floating ip %s from interface %s",
                          ip_cidr, ipintf)
                self.pf.remove_anchor([interface_name, ip_cidr.split('/')[0]])
                ipintf.delete_address(ip_cidr, addrcheck=False)
        return fip_statuses

    def delete(self, agent):
        self.router['gw_port'] = None
        self.router[l3_constants.INTERFACE_KEY] = []
        self.router[l3_constants.FLOATINGIP_KEY] = []
        self.process_delete(agent)
        self.disable_radvd()

    def internal_network_added(self, port):
        internal_dlname = self.get_internal_device_name(port['id'])
        LOG.debug("adding internal network: port(%s), interface(%s)",
                  port['id'], internal_dlname)
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

        port_subnet = port['subnets'][0]['cidr']
        ipversion = netaddr.IPNetwork(port_subnet).version
        rules = []
        # if metadata is enabled, then we need to redirect all the packets
        # arriving at 169.254.169.254:80 to neutron-metadata-proxy server
        # listening at self.agent_conf.metadata_port
        if self.agent_conf.enable_metadata_proxy and ipversion == 4:
            rules.append('pass in quick proto tcp to 169.254.169.254/32 '
                         'port 80 rdr-to 127.0.0.1 port %s label metadata_%s'
                         % (self.agent_conf.metadata_port, internal_dlname))

        # Since we support shared router model, we need to block the new
        # internal port from reaching other tenant's ports. However, if
        # allow_forwarding_between_networks is set, then we need to
        # allow forwarding of packets between same tenant's ports.
        block_tblname = 'block_%s' % internal_dlname
        rules.append('block in quick to <%s> label %s' %
                     (block_tblname, block_tblname))
        if self.agent_conf.allow_forwarding_between_networks:
            allow_tblname = 'allow_%s' % internal_dlname
            rules.append('pass in quick to <%s> reply-to %s label %s' %
                         (allow_tblname, internal_dlname, allow_tblname))

        # finally add all the rules in one shot
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
        # then we need to add Policy Based Routing (PBR) for both inbound
        # and outbound for this internal network
        external_dlname = self.get_external_device_name(ex_gw_port['id'])
        label = 'pbr_%s' % internal_dlname
        pbr_rules = ['pass in quick to !%s route-to {(%s %s)} label %s_in' %
                     (port_subnet, external_dlname, ex_gw_ip, label)]
        pbr_rules.append('pass out quick received-on %s reply-to %s@%s '
                         'label %s_out' % (external_dlname, ex_gw_ip,
                                           external_dlname, label))

        self.pf.add_rules(pbr_rules, [internal_dlname, 'pbr'])
        if self._snat_enabled:
            ex_gw_port_ip = ex_gw_port['fixed_ips'][0]['ip_address']
            label = 'snat_%s' % internal_dlname
            snat_rule = ('pass out quick from %s to any nat-to %s label %s '
                         'reply-to %s' % (port_subnet, ex_gw_port_ip, label,
                                          internal_dlname))
            self.pf.add_rules([snat_rule], [external_dlname, internal_dlname])

    def internal_network_removed(self, port):
        internal_dlname = self.get_internal_device_name(port['id'])
        LOG.debug("removing internal network: port(%s) interface(%s)",
                  port['id'], internal_dlname)
        # remove the anchor and tables associated with this internal port
        self.pf.remove_anchor_recursively([internal_dlname])
        if self.ex_gw_port and self._snat_enabled:
            external_dlname = self.\
                get_external_device_name(self.ex_gw_port['id'])
            self.pf.remove_anchor_recursively([external_dlname,
                                               internal_dlname])
        if net_lib.Datalink.datalink_exists(internal_dlname):
            self.driver.unplug(internal_dlname)

    def _get_existing_devices(self):
        return net_lib.Datalink.show_link()

    def internal_network_updated(self, interface_name, ip_cidrs):
        pass

    def _apply_common_rules(self, all_subnets, internal_ports):
        v4_subnets = [subnet for subnet in all_subnets
                      if netaddr.IPNetwork(subnet).version == 4]
        if not v4_subnets:
            return

        # add rule for metadata and broadcast
        allsubnets_tblname = "all_v4_subnets"
        common_aname = "common"
        self.pf.replace_table_entry(allsubnets_tblname, v4_subnets,
                                    [common_aname])
        rules = []
        # don't forward broadcast packets out of the internal subnet
        rules.append('pass in quick from <%s> to 255.255.255.255 label '
                     '%s_bcast' % (allsubnets_tblname, common_aname))
        self.pf.add_rules(rules, [common_aname])

    def _pre_setup_pf_rules(self, new_ports, old_ports, internal_ports):
        """We are going to do some amount of book keeping (for later use) and
        also pre-setup PF skeleton rules ahead of time to improve PF setup
        time.
        """

        # Process PF anchor rules for internal ports in bulk as this
        # significantly improves the PF setup time. Capture the anchor
        # rules that will be placed under _auto/neutron:l3:agent.
        new_anchor_rules = set()
        for p in new_ports:
            port_id = p['id']
            tenant_id = p['tenant_id']
            subnet = p['subnets'][0]['cidr']
            internal_dlname = self.get_internal_device_name(port_id)
            anchor_rule = 'anchor "%s/*" on %s all' % (internal_dlname,
                                                       internal_dlname)
            new_anchor_rules.add(anchor_rule)
            ipnet = netaddr.IPNetwork(subnet)
            if ipnet.version == 4:
                self.ipnet_gwportname[ipnet] = internal_dlname
            # Capture all the subnets across all tenants and subnets
            # per-tenant. We will setup PF tables for each internal network
            # ahead of time
            self.tenant_subnets['all_tenants'].add(subnet)
            if tenant_id not in self.tenant_subnets:
                self.tenant_subnets[tenant_id] = set()
            self.tenant_subnets[tenant_id].add(subnet)

        old_anchor_rules = set()
        for p in old_ports:
            port_id = p['id']
            tenant_id = p['tenant_id']
            subnet = p['subnets'][0]['cidr']
            internal_dlname = self.get_internal_device_name(port_id)
            anchor_rule = 'anchor "%s/*" on %s all' % (internal_dlname,
                                                       internal_dlname)
            old_anchor_rules.add(anchor_rule)
            ipnet = netaddr.IPNetwork(subnet)
            if ipnet.version == 4:
                self.ipnet_gwportname.pop(ipnet, None)
            self.tenant_subnets['all_tenants'].discard(subnet)
            if tenant_id in self.tenant_subnets:
                self.tenant_subnets[tenant_id].discard(subnet)

        existing_anchor_rules = set(self.pf.list_anchor_rules())
        final_anchor_rules = ((existing_anchor_rules | new_anchor_rules) -
                              old_anchor_rules)
        # add an anchor rule to capture rules common amongst all the
        # internal ports under 'common' anchor
        if internal_ports:
            final_anchor_rules.add('anchor "common" all')
            # add rule for metadata and broadcast for all tenant's networks
            self._apply_common_rules(self.tenant_subnets['all_tenants'],
                                     internal_ports)
        else:
            final_anchor_rules.discard('anchor "common" all')
            # Now that there are no internal ports, remove the common anchor
            # that captures rules common amongst all the internal ports
            self.pf.remove_anchor_recursively(['common'])
        self.pf.add_rules(list(sorted(final_anchor_rules)))

        # Since we support shared router model, we need to block the new
        # internal port from reaching other tenant's ports. However, if
        # allow_forwarding_between_networks is set, then we need to
        # allow forwarding of packets between same tenant's ports
        block_subnets = set()
        allow_subnets = set()
        for p in internal_ports:
            subnet = p['subnets'][0]['cidr']
            tenant_id = p['tenant_id']
            if self.agent_conf.allow_forwarding_between_networks:
                allow_subnets = self.tenant_subnets[tenant_id] - set([subnet])
                block_subnets = (self.tenant_subnets['all_tenants'] -
                                 self.tenant_subnets[tenant_id])
            else:
                block_subnets = (self.tenant_subnets['all_tenants'] -
                                 set([subnet]))
            # add table entry in the global scope
            internal_dlname = self.get_internal_device_name(p['id'])
            block_tblname = "block_%s" % internal_dlname
            self.pf.replace_table_entry(block_tblname, list(block_subnets),
                                        [internal_dlname, 'normal'])
            if allow_subnets:
                allow_tblname = "allow_%s" % internal_dlname
                self.pf.replace_table_entry(allow_tblname, list(allow_subnets),
                                            [internal_dlname, 'normal'])

    def _process_internal_ports(self, pd):
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

        if old_ports or new_ports:
            self._pre_setup_pf_rules(new_ports, old_ports, internal_ports)

        enable_ra = False
        for p in new_ports:
            self.internal_network_added(p)
            LOG.debug("appending port %s to internal_ports cache", p)
            self.internal_ports.append(p)
            enable_ra = enable_ra or self._port_has_ipv6_subnet(p)
            for subnet in p['subnets']:
                if ipv6_utils.is_ipv6_pd_enabled(subnet):
                    interface_name = self.get_internal_device_name(p['id'])
                    pd.enable_subnet(self.router_id, subnet['id'],
                                     subnet['cidr'],
                                     interface_name, p['mac_address'])

        for p in old_ports:
            self.internal_network_removed(p)
            LOG.debug("removing port %s from internal_ports cache", p)
            self.internal_ports.remove(p)
            enable_ra = enable_ra or self._port_has_ipv6_subnet(p)
            for subnet in p['subnets']:
                if ipv6_utils.is_ipv6_pd_enabled(subnet):
                    pd.disable_subnet(self.router_id, subnet['id'])

#         updated_cidres = []
#         if updated_ports:
#             for index, p in enumerate(internal_ports):
#                 if not updated_ports.get(p['id']):
#                     continue
#                 self.internal_ports[index] = updated_ports[p['id']]
#                 interface_name = self.get_internal_device_name(p['id'])
#                 ip_cidrs = common_utils.fixed_ip_cidrs(p['fixed_ips'])
#                 LOG.debug("updating internal network for port %s", p)
#                 updated_cidrs += ip_cidrs

#                 self.driver.init_l3(interface_name, ip_cidrs=ip_cidrs,
#                         namespace=self.ns_name)
#                 enable_ra = enable_ra or self._port_has_ipv6_subnet(p)

#         # Check if there is any pd prefix update
#         for p in internal_ports:
#             if p['id'] in (set(current_port_ids) & set(existing_port_ids)):
#                 for subnet in p.get('subnets', []):
#                     if ipv6_utils.is_ipv6_pd_enabled(subnet):
#                         old_prefix = pd.update_subnet(self.router_id,
#                                                       subnet['id'],
#                                                       subnet['cidr'])
#                         if old_prefix:
#                             self._internal_network_updated(p, subnet['id'],
#                                                            subnet['cidr'],
#                                                            old_prefix,
#                                                            updated_cidrs)
#                             enable_ra = True
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
            pd.remove_stale_ri_ifname(self.router_id, stale_dev)
            self.driver.unplug(stale_dev)

    # TODO(gmoodalb): need to do more work on ipv6 gateway
    def external_gateway_added(self, ex_gw_port, external_dlname):
        LOG.debug("External gateway added: port(%s), interface(%s)",
                  ex_gw_port, external_dlname)
        # TODO(gmoodalb): add MTU to plug()?
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
                label = 'pbr_%s' % internal_dlname
                pbr_rules = ['pass in quick to !%s route-to {(%s %s)} '
                             'label %s_in' % (port_subnet, external_dlname,
                                              gw_ip, label)]
                pbr_rules.append('pass out quick received-on %s reply-to %s@%s'
                                 ' label %s_out' % (external_dlname, gw_ip,
                                                    external_dlname, label))
                self.pf.add_rules(pbr_rules, [internal_dlname, 'pbr'])

    def external_gateway_updated(self, ex_gw_port, external_dlname):
        # There is nothing to do on Solaris
        pass

    def external_gateway_removed(self, ex_gw_port, external_dlname):
        LOG.debug("External gateway removed: port(%s), interface(%s)",
                  ex_gw_port, external_dlname)
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
            self.driver.unplug(external_dlname,
                               self.agent_conf.external_network_bridge)

    def _process_external_gateway(self, ex_gw_port, pd):
        # TODO(Carl) Refactor to clarify roles of ex_gw_port vs self.ex_gw_port
        ex_gw_port_id = (ex_gw_port and ex_gw_port['id'] or
                         self.ex_gw_port and self.ex_gw_port['id'])

        ex_gw_port_status = None
        interface_name = None
        if ex_gw_port_id:
            interface_name = self.get_external_device_name(ex_gw_port_id)
        if ex_gw_port:
            if not self.ex_gw_port:
                self.external_gateway_added(ex_gw_port, interface_name)
                pd.add_gw_interface(self.router['id'], interface_name)
                ex_gw_port_status = 'added'
            elif not self._gateway_ports_equal(ex_gw_port, self.ex_gw_port):
                self.external_gateway_updated(ex_gw_port, interface_name)
                ex_gw_port_status = 'updated'
        elif not ex_gw_port and self.ex_gw_port:
            self.external_gateway_removed(self.ex_gw_port, interface_name)
            pd.remove_gw_interface(self.router['id'])
            ex_gw_port_status = 'removed'

        # Remove any external stale router interfaces (i.e., l3e.. VNICs)
        existing_devices = self._get_existing_devices()
        stale_devs = [dev for dev in existing_devices
                      if dev.startswith(EXTERNAL_DEV_PREFIX) and
                      dev != interface_name]
        for stale_dev in stale_devs:
            LOG.debug(_('Deleting stale external router device: %s'),
                      stale_dev)
            self.driver.unplug(stale_dev)

        # Process SNAT rules for external gateway
        gw_port = self._router.get('gw_port')
        self._handle_router_snat_rules(gw_port, interface_name,
                                       ex_gw_port_status)

    def external_gateway_snat_rules(self, ex_gw_port_ip, external_dlname):
        rules = {}
        for port in self.internal_ports:
            ip_cidr = port['subnets'][0]['cidr']
            if netaddr.IPNetwork(ip_cidr).version == 4:
                internal_dlname = self.get_internal_device_name(port['id'])
                label = 'snat_%s' % internal_dlname
                rule = ('pass out quick from %s to any nat-to %s label %s '
                        'reply-to %s' % (ip_cidr, ex_gw_port_ip, label,
                                         internal_dlname))
                rules[internal_dlname] = [rule]

        return rules

    def _handle_router_snat_rules(self, ex_gw_port, external_dlname,
                                  ex_gw_port_status):
        # Todo(gmoodalb): need this when we support address_scope
        # self.process_external_port_address_scope_routing(iptables_manager)

        # Remove all the old SNAT rules
        # This is safe because if use_namespaces is set as False
        # then the agent can only configure one router, otherwise
        # each router's SNAT rules will be in their own namespace
        if ex_gw_port_status in ['removed', 'updated']:
            snat_anchors = self.pf.list_anchors([external_dlname])
            for snat_anchor in snat_anchors:
                if "/l3i" in snat_anchor:
                    self.pf.remove_anchor(snat_anchor.split('/')[-2:])

        # And add them back if the action is add_rules
        if ex_gw_port_status in ['added', 'updated']:
            # NAT rules are added only if ex_gw_port has an IPv4 address
            ex_gw_port_ip = ex_gw_port['fixed_ips'][0]['ip_address']
            if netaddr.IPAddress(ex_gw_port_ip).version != 4:
                return
            port_rules = self.external_gateway_snat_rules(ex_gw_port_ip,
                                                          external_dlname)
            for internal_dlname, rules in port_rules.iteritems():
                self.pf.add_rules(rules, [external_dlname, internal_dlname])

    def process_external(self, agent):
        fip_statuses = {}
        try:
            ex_gw_port = self.get_ex_gw_port()
            self._process_external_gateway(ex_gw_port, agent.pd)
            # TODO(Carl) Return after setting existing_floating_ips and
            # still call update_fip_statuses?
            if not ex_gw_port:
                return

            # Once NAT rules for floating IPs are safely in place
            # configure their addresses on the external gateway port
            interface_name = self.get_external_device_name(ex_gw_port['id'])
            fip_statuses = self.configure_fip_addresses(interface_name)
        except n_exc.FloatingIpSetupException:
                # All floating IPs must be put in error state
                LOG.exception(_LE("Failed to process floating IPs."))
                fip_statuses = self.put_fips_in_error_state()
        finally:
            self.update_fip_statuses(agent, fip_statuses)

    def process_external_port_address_scope_routing(self, iptables_manager):
        pass

    def process_address_scope(self):
        pass


class L3NATAgent(l3_agent.L3NATAgentWithStateReport):
    OPTS = [
        cfg.BoolOpt('allow_forwarding_between_networks', default=False,
                    help=_("Allow forwarding of packets between tenant's "
                           "networks")),
    ]

    def __init__(self, host, conf=None):
        cfg.CONF.register_opts(self.OPTS)
        cfg.CONF.register_opts(interface.OPTS)
        super(L3NATAgent, self).__init__(host=host, conf=conf)
        cfg.CONF.register_opts(neutron_vpnaas.vpn_agent_opts, 'vpnagent')
        self.service = vpn_service.VPNService(self)
        self.device_drivers = self.service.load_device_drivers(host)

    def _check_config_params(self):
        """Check items in configuration files.

        Check for required and invalid configuration items.
        The actual values are not verified for correctness.
        """
        if not self.conf.interface_driver:
            msg = _LE('An interface driver must be specified')
            LOG.error(msg)
            raise SystemExit(1)

        if not self.conf.router_id:
            msg = _LE('Router id (router_id) is required to be set.')
            LOG.error(msg)
            raise SystemExit(1)

        if self.conf.ipv6_gateway:
            # ipv6_gateway configured. Check for valid v6 link-local address.
            try:
                msg = _LE("%s used in config as ipv6_gateway is not a valid "
                          "IPv6 link-local address."),
                ip_addr = netaddr.IPAddress(self.conf.ipv6_gateway)
                if ip_addr.version != 6 or not ip_addr.is_link_local():
                    LOG.error(msg, self.conf.ipv6_gateway)
                    raise SystemExit(1)
            except netaddr.AddrFormatError:
                LOG.error(msg, self.conf.ipv6_gateway)
                raise SystemExit(1)

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

        # We don't support namespaces so only process the router associated
        # with the configured agent id.
        if (router['id'] != self.conf.router_id):
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
