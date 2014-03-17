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
Based off generic l3_agent (quantum/agent/l3_agent) code
"""

from oslo.config import cfg

from quantum.agent import l3_agent
from quantum.agent.solaris import interface
from quantum.agent.solaris import ipfilters_manager
from quantum.agent.solaris import net_lib
from quantum.common import constants as l3_constants
from quantum.openstack.common import log as logging


LOG = logging.getLogger(__name__)
INTERNAL_DEV_PREFIX = 'l3i'
EXTERNAL_DEV_PREFIX = 'l3e'


class RouterInfo(object):

    def __init__(self, router_id, root_helper, use_namespaces, router):
        self.router_id = router_id
        self.ex_gw_port = None
        self.internal_ports = []
        self.floating_ips = []
        self.router = router
        self.ipfilters_manager = ipfilters_manager.IpfiltersManager()
        self.routes = []


class EVSL3NATAgent(l3_agent.L3NATAgent):

    RouterInfo = RouterInfo

    OPTS = [
        cfg.StrOpt('external_network_bridge', default='',
                   help=_("Name of bridge used for external network "
                          "traffic.")),
        cfg.StrOpt('interface_driver',
                   help=_("The driver used to manage the virtual "
                          "interface.")),
        cfg.BoolOpt('use_namespaces', default=False,
                    help=_("Allow overlapping IP.")),
        cfg.StrOpt('router_id',
                   help=_("If namespaces is disabled, the l3 agent can only"
                          " configure a router that has the matching router "
                          "ID.")),
        cfg.BoolOpt('handle_internal_only_routers', default=True,
                    help=_("Agent should implement routers with no gateway")),
        cfg.StrOpt('gateway_external_network_id', default='',
                   help=_("UUID of external network for routers implemented "
                          "by the agents.")),
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
        if not cfg.CONF.router_id:
            raise SystemExit(_("router_id option needs to be set"))

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
        dname = (EXTERNAL_DEV_PREFIX + port_id)[:13]
        dname += '_0'
        return dname.replace('-', '_')

    def external_gateway_added(self, ri, ex_gw_port, internal_cidrs):
        pass

    def external_gateway_removed(self, ri, ex_gw_port, internal_cidrs):
        pass

    def _get_ippool_name(self, mac_address):
        # generate a unique-name for ippool(1m) from that last 3
        # bytes of mac-address
        mac_suffix = mac_address.split(':')[3:]
        return int("".join(mac_suffix), 16)

    def internal_network_added(self, ri, ex_gw_port, port):

        internal_dlname = self.get_internal_device_name(port['id'])
        if not net_lib.Datalink.datalink_exists(internal_dlname):
            self.driver.plug(port['tenant_id'], port['network_id'], port['id'],
                             internal_dlname)
        self.driver.init_l3(internal_dlname, [port['ip_cidr']])

        # add ippool(1m) for the new internal port
        new_ippool_name = self._get_ippool_name(port['mac_address'])
        ri.ipfilters_manager.add_ippool(new_ippool_name, None)

        # walk through the other internal ports and retrieve their
        # cidrs and at the same time add the new internal port's
        # cidr to them
        subnet_cidr = port['subnet']['cidr']
        other_subnet_cidrs = []
        for oip in ri.internal_ports:
            if oip['mac_address'] != port['mac_address']:
                if (self.conf.allow_forwarding_between_networks and
                    oip['tenant_id'] == port['tenant_id']):
                    continue
                other_subnet_cidrs.append(oip['subnet']['cidr'])
                ippool_name = self._get_ippool_name(oip['mac_address'])
                ri.ipfilters_manager.add_ippool(ippool_name, [subnet_cidr])
        # update the new port's pool with other port's cidrs
        ri.ipfilters_manager.add_ippool(new_ippool_name, other_subnet_cidrs)

        # now setup the IPF rule
        rules = ['block in quick on %s from %s to pool/%d' %
                 (internal_dlname, subnet_cidr, new_ippool_name)]
        ri.ipfilters_manager.add_ipf_rules(rules)

    def internal_network_removed(self, ri, ex_gw_port, port):
        internal_dlname = self.get_internal_device_name(port['id'])
        if net_lib.Datalink.datalink_exists(internal_dlname):
            self.driver.fini_l3(internal_dlname)
            self.driver.unplug(internal_dlname)

        # remove all the IP filter rules that we added during addition.
        ippool_name = self._get_ippool_name(port['mac_address'])
        rules = ['block in quick on %s from %s to pool/%d' %
                 (internal_dlname, port['subnet']['cidr'], ippool_name)]
        ri.ipfilters_manager.remove_ipf_rules(rules)
        # remove the ippool
        ri.ipfilters_manager.remove_ippool(ippool_name, None)
        for internal_port in ri.internal_ports:
            if (self.conf.allow_forwarding_between_networks and
                internal_port['tenant_id'] == port['tenant_id']):
                continue
            ippool_name = \
                self._get_ippool_name(internal_port['mac_address'])
            ri.ipfilters_manager.remove_ippool(ippool_name,
                                               internal_port['subnet']['cidr'])

    def floating_ip_added(self, ri, ex_gw_port, floating_ip, fixed_ip):
        floating_ipcidr = str(floating_ip) + '/32'
        fixed_ipcidr = str(fixed_ip) + '/32'
        #ifname = self.get_external_device_name(ex_gw_port['id'])
        ifname = self.conf.external_network_datalink
        ipif = net_lib.IPInterface(ifname)
        ipif.create_address(floating_ipcidr)

        nat_rules = ['bimap %s %s -> %s' %
                     (ifname, fixed_ipcidr, floating_ipcidr)]
        ri.ipfilters_manager.add_nat_rules(nat_rules)

    def floating_ip_removed(self, ri, ex_gw_port, floating_ip, fixed_ip):
        floating_ipcidr = str(floating_ip) + '/32'
        fixed_ipcidr = str(fixed_ip) + '/32'
        ifname = self.conf.external_network_datalink
        ipif = net_lib.IPInterface(ifname)
        ipif.delete_address(floating_ipcidr)

        nat_rules = ['bimap %s %s -> %s' %
                     (ifname, fixed_ipcidr, floating_ipcidr)]
        ri.ipfilters_manager.remove_nat_rules(nat_rules)

    def routes_updated(self, ri):
        pass
