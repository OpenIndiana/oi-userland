# Copyright 2012, Nachi Ueno, NTT MCL, Inc.
# All Rights Reserved.
#
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
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

import collections

import netaddr
from oslo_config import cfg
from oslo_log import log as logging
import six

from neutron._i18n import _LI
from neutron.agent.common import ovs_lib
from neutron.agent import firewall
from neutron.agent.solaris import packetfilter
from neutron.common import constants
from neutron.common import utils as c_utils


LOG = logging.getLogger(__name__)
ICMPV6_ALLOWED_UNSPEC_ADDR_TYPES = [131, 135, 143]

DIRECTION_PF_PARAM = {firewall.INGRESS_DIRECTION: 'in',
                      firewall.EGRESS_DIRECTION: 'out'}


class PFBaseOVS(ovs_lib.BaseOVS):
    def get_port_by_id(self, port_id):
        ports = self.ovsdb.db_find(
            'Interface', ('external_ids', '=', {'iface-id': port_id}),
            columns=['name']).execute()
        if ports:
            return ports[0]['name']
        return None


class PFFirewallDriver(firewall.FirewallDriver):
    """Driver which enforces security groups through PF rules.

    Please look at neutron.agent.firewall.FirewallDriver for more information
    on how the methods below are called from the Neutron Open vSwitch agent. It
    all starts at prepare_port_filter() and then _setup_pf_rules() has all the
    PF based logic to add correct rules on guest instance's port.
    """

    def __init__(self):
        self.pf = packetfilter.PacketFilter("_auto/neutron:ovs:agent",
                                            layer2=True)
        # List of port which has security group
        self.filtered_ports = {}
        self.unfiltered_ports = {}
        # List of security group rules for ports residing on this host
        self.sg_rules = {}
        # List of security group member ips for ports residing on this host
        self.sg_members = collections.defaultdict(
            lambda: collections.defaultdict(list))
        # Every PF rule needs to be labeled so that we can later kill the state
        # associated with that rule (using pfctl -k label -k 110). It is hard
        # to come up with a meaningfully named label for each PF rule, so we
        # are resorting to numbers here.
        self.label_num = 100
        self.portid_to_devname = {}

    def prepare_port_filter(self, port):
        LOG.debug("Preparing device (%s) filter", port['device'])
        self._setup_pf_rules(port)

    def apply_port_filter(self, port):
        """We never call this method

        It exists here to override abstract method of parent abstract class.
        """
        pass

    def update_port_filter(self, port):
        LOG.debug("Updating device (%s) filter", port['device'])
        self._setup_pf_rules(port, update=True)

    def remove_port_filter(self, port):
        LOG.debug("Removing device (%s) filter", port['device'])
        self.unfiltered_ports.pop(port['device'], None)
        self.filtered_ports.pop(port['device'], None)
        self._remove_rule_port_sec(port)

    @property
    def ports(self):
        return dict(self.filtered_ports, **self.unfiltered_ports)

    def update_security_group_rules(self, sg_id, sg_rules):
        LOG.debug("Update rules of security group %s(%s)" % (sg_id, sg_rules))
        self.sg_rules[sg_id] = sg_rules

    def update_security_group_members(self, sg_id, sg_members):
        LOG.debug("Update members of security group %s(%s)" %
                  (sg_id, sg_members))
        self.sg_members[sg_id] = collections.defaultdict(list, sg_members)

    def security_group_updated(self, action_type, sec_group_ids,
                               device_ids=None):
        # TODO(gmoodalb): Extend this later to optimize handling of security
        # groups update
        pass

    def _get_label_number(self):
        self.label_num += 1
        return self.label_num

    def _remove_rule_port_sec(self, port):
        device_name = self.portid_to_devname.pop(port['id'], None)
        if not device_name:
            LOG.info(_LI("Could not find port: %s. Failed to remove PF rules "
                         "for that port"), port['id'])
            return
        LOG.debug("Removing PF rules for device_name(%s)" % device_name)
        # we need to remove both ingress and egress
        if '/' in device_name:
            instance_name, datalink = device_name.split('/')
            instance_name = instance_name.split(':')[1]
            ingress = '%s_in' % datalink
            egress = '%s_out' % datalink
        else:
            instance_name = device_name
            ingress = 'in'
            egress = 'out'
        existing_anchor_rules = set(self.pf.list_anchor_rules([instance_name]))
        existing_anchor_rules.discard('anchor "%s" in on %s all' %
                                      (ingress, device_name))
        existing_anchor_rules.discard('anchor "%s" out on %s all' %
                                      (egress, device_name))
        self.pf.add_rules(list(existing_anchor_rules), [instance_name])
        if existing_anchor_rules:
            self.pf.remove_anchor_recursively([instance_name, ingress])
            self.pf.remove_anchor_recursively([instance_name, egress])
        else:
            self.pf.remove_anchor_recursively([instance_name])

    def _setup_pf_rules(self, port, update=False):
        if not firewall.port_sec_enabled(port):
            self.unfiltered_ports[port['device']] = port
            self.filtered_ports.pop(port['device'], None)
            self._remove_rule_port_sec(port)
        else:
            self.filtered_ports[port['device']] = port
            self.unfiltered_ports.pop(port['device'], None)
            if update:
                self._remove_rule_port_sec(port)
            self._add_rules_by_security_group(port, firewall.INGRESS_DIRECTION)
            self._add_rules_by_security_group(port, firewall.EGRESS_DIRECTION)

    def _get_device_name(self, port):
        bridge = PFBaseOVS()
        device_name = bridge.get_port_by_id(port['id'])
        if '/' in device_name:
            device_name = 'dl:' + device_name
        return device_name

    def _split_sgr_by_ethertype(self, security_group_rules):
        ipv4_sg_rules = []
        ipv6_sg_rules = []
        for rule in security_group_rules:
            if rule.get('ethertype') == constants.IPv4:
                ipv4_sg_rules.append(rule)
            elif rule.get('ethertype') == constants.IPv6:
                if rule.get('protocol') in ['icmp', 'icmp6']:
                    rule['protocol'] = 'ipv6-icmp'
                ipv6_sg_rules.append(rule)
        return ipv4_sg_rules, ipv6_sg_rules

    def _select_sgr_by_direction(self, port, direction):
        return [rule
                for rule in port.get('security_group_rules', [])
                if rule['direction'] == direction]

    def _spoofing_rule(self, port, device_name, ipv4_rules, ipv6_rules):
        # Fixed rules for traffic sourced from unspecified addresses: 0.0.0.0
        # and ::
        # Allow dhcp client discovery and request
        ipv4_rules.append('pass out on %s proto udp from 0.0.0.0/32 port 68 '
                          'to 255.255.255.255/32 port 67 label "%s"' %
                          (device_name, self._get_label_number()))

        # Allow neighbor solicitation and multicast listener discovery
        # from the unspecified address for duplicate address detection
        for icmp6_type in ICMPV6_ALLOWED_UNSPEC_ADDR_TYPES:
            ipv6_rules.append('pass out on %s inet6 proto ipv6-icmp '
                              'from ::/128 to ff02::/16 icmp6-type %s '
                              'label "%s"' % (device_name, icmp6_type,
                                              self._get_label_number()))

        # Fixed rules for traffic after source address is verified
        # Allow dhcp client renewal and rebinding
        ipv4_rules.append('pass out on %s proto udp from port 68 to port 67 '
                          'label "%s"' % (device_name,
                                          self._get_label_number()))

        # Drop Router Advts from the port.
        ipv6_rules.append('block out quick on %s inet6 proto ipv6-icmp '
                          'icmp6-type %s label "%s"' %
                          (device_name, constants.ICMPV6_TYPE_RA,
                           self._get_label_number()))
        # Allow IPv6 ICMP traffic
        ipv6_rules.append('pass out on %s inet6 proto ipv6-icmp label "%s"' %
                          (device_name, self._get_label_number()))
        # Allow IPv6 DHCP Client traffic
        ipv6_rules.append('pass out on %s inet6 proto udp from port 546 '
                          'to port 547 label "%s"' %
                          (device_name, self._get_label_number()))

    def _drop_dhcp_rule(self, device_name, ipv4_rules, ipv6_rules):
        # Drop dhcp packet from VM
        ipv4_rules.append('block out quick on %s proto udp from port 67 '
                          'to port 68 label "%s"' %
                          (device_name, self._get_label_number()))
        ipv6_rules.append('block out quick on %s inet6 proto udp '
                          'from port 547 to port 546 label "%s"' %
                          (device_name, self._get_label_number()))

    def _accept_inbound_icmpv6(self, device_name, ipv6_pf_rules):
        # Allow multicast listener, neighbor solicitation and
        # neighbor advertisement into the instance
        for icmp6_type in constants.ICMPV6_ALLOWED_TYPES:
            ipv6_pf_rules.append('pass in on %s inet6 proto ipv6-icmp '
                                 'icmp6-type %s label "%s"' %
                                 (device_name, icmp6_type,
                                  self._get_label_number()))

    def _select_sg_rules_for_port(self, port, direction):
        """Select rules from the security groups the port is member of."""
        port_sg_ids = port.get('security_groups', [])
        port_rules = []

        for sg_id in port_sg_ids:
            for rule in self.sg_rules.get(sg_id, []):
                if rule['direction'] == direction:
                    port_rules.extend(
                        self._expand_sg_rule_with_remote_ips(
                            rule, port, direction))
        return port_rules

    def _expand_sg_rule_with_remote_ips(self, rule, port, direction):
        """Expand a remote group rule to rule per remote group IP."""
        remote_group_id = rule.get('remote_group_id')
        if remote_group_id:
            ethertype = rule['ethertype']
            port_ips = port.get('fixed_ips', [])
            LOG.debug("Expanding rule: %s with remote IPs: %s" %
                      (rule, self.sg_members[remote_group_id][ethertype]))
            for ip in self.sg_members[remote_group_id][ethertype]:
                if ip not in port_ips:
                    ip_rule = rule.copy()
                    direction_ip_prefix = firewall.DIRECTION_IP_PREFIX[
                        direction]
                    ip_prefix = str(netaddr.IPNetwork(ip).cidr)
                    ip_rule[direction_ip_prefix] = ip_prefix
                    yield ip_rule
        else:
            yield rule

    def _get_remote_sg_ids(self, port, direction=None):
        sg_ids = port.get('security_groups', [])
        remote_sg_ids = {constants.IPv4: set(), constants.IPv6: set()}
        for sg_id in sg_ids:
            for rule in self.sg_rules.get(sg_id, []):
                if not direction or rule['direction'] == direction:
                    remote_sg_id = rule.get('remote_group_id')
                    ether_type = rule.get('ethertype')
                    if remote_sg_id and ether_type:
                        remote_sg_ids[ether_type].add(remote_sg_id)
        return remote_sg_ids

    def _add_pf_rules(self, port, device_name, direction, ipv4_pf_rules,
                      ipv6_pf_rules):
        if '/' in device_name:
            instance_name, datalink = device_name.split('/')
            instance_name = instance_name.split(':')[1]
        else:
            instance_name, datalink = (device_name, "")
        self.pf.add_nested_anchor_rule(None, instance_name, None)
        if direction == firewall.INGRESS_DIRECTION:
            subanchor = '%s%s' % (datalink, '_in' if datalink else 'in')
            new_anchor_rule = ['anchor "%s" in on %s all' % (subanchor,
                                                             device_name)]
        else:
            subanchor = '%s%s' % (datalink, '_out' if datalink else 'out')
            new_anchor_rule = ['anchor "%s" out on %s all' % (subanchor,
                                                              device_name)]
        existing_anchor_rules = self.pf.list_anchor_rules([instance_name])
        final_anchor_rules = set(existing_anchor_rules) | set(new_anchor_rule)
        self.pf.add_rules(list(final_anchor_rules), [instance_name])

        # self.pf.add_nested_anchor_rule(None, anchor_name, anchor_option)
        self.pf.add_rules(ipv4_pf_rules + ipv6_pf_rules,
                          [instance_name, subanchor])
        self.portid_to_devname[port['id']] = device_name

    def _add_block_everything(self, device_name, direction, ipv4_pf_rules,
                              ipv6_pf_rules):
        ''' Add a generic block everything rule. The default security group
        in OpenStack adds 'pass all egress traffic' and prevents all the
        incoming traffic'''
        ipv4_pf_rules.append('block %s on %s label "%s"' %
                             (DIRECTION_PF_PARAM[direction], device_name,
                              self._get_label_number()))
        ipv6_pf_rules.append('block %s on %s inet6 label "%s"' %
                             (DIRECTION_PF_PARAM[direction], device_name,
                              self._get_label_number()))

    def _add_rules_by_security_group(self, port, direction):
        LOG.debug("Adding rules for Port: %s", port)

        device_name = self._get_device_name(port)
        if not device_name:
            LOG.info(_LI("Could not find port: %s on the OVS bridge. Failed "
                         "to add PF rules for that port"), port['id'])
            return
        # select rules for current port and direction
        security_group_rules = self._select_sgr_by_direction(port, direction)
        security_group_rules += self._select_sg_rules_for_port(port, direction)
        # split groups by ip version
        # for ipv4, 'pass' will be used
        # for ipv6, 'pass inet6' will be used
        ipv4_sg_rules, ipv6_sg_rules = self._split_sgr_by_ethertype(
            security_group_rules)
        ipv4_pf_rules = []
        ipv6_pf_rules = []
        self._add_block_everything(device_name, direction, ipv4_pf_rules,
                                   ipv6_pf_rules)
        # include fixed egress/ingress rules
        if direction == firewall.EGRESS_DIRECTION:
            self._add_fixed_egress_rules(port, device_name, ipv4_pf_rules,
                                         ipv6_pf_rules)
        elif direction == firewall.INGRESS_DIRECTION:
            self._accept_inbound_icmpv6(device_name, ipv6_pf_rules)
        # include IPv4 and IPv6 iptable rules from security group
        LOG.debug("Converting %s IPv4 SG rules: %s" %
                  (direction, ipv4_sg_rules))
        ipv4_pf_rules += self._convert_sgr_to_pfr(device_name, direction,
                                                  ipv4_sg_rules)
        LOG.debug("... to %s IPv4 PF rules: %s" % (direction, ipv4_pf_rules))
        LOG.debug("Converting %s IPv6 SG rules: %s" %
                  (direction, ipv6_sg_rules))
        ipv6_pf_rules += self._convert_sgr_to_pfr(device_name, direction,
                                                  ipv6_sg_rules)
        LOG.debug("... to %s IPv6 PF rules: %s" % (direction, ipv6_pf_rules))

        self._add_pf_rules(port, device_name, direction, ipv4_pf_rules,
                           ipv6_pf_rules)

    def _add_fixed_egress_rules(self, port, device_name, ipv4_pf_rules,
                                ipv6_pf_rules):
        self._spoofing_rule(port, device_name, ipv4_pf_rules, ipv6_pf_rules)
        self._drop_dhcp_rule(device_name, ipv4_pf_rules, ipv6_pf_rules)

    def _protocol_param(self, protocol, pf_rule):
        if protocol:
            pf_rule.append('proto %s' % protocol)

    def _port_param(self, protocol, port_range_min, port_range_max, pf_rule):
        if port_range_min is None:
            return
        if protocol in ('tcp', 'udp'):
            if port_range_min == port_range_max:
                pf_rule.append('port %s' % port_range_min)
            else:
                pf_rule.append('port %s:%s' % (port_range_min,
                                               port_range_max))
        elif protocol in ('icmp', 'ipv6-icmp'):
            icmp_type = 'icmp-type' if protocol == 'icmp' else 'icmp6-type'
            pf_rule.append('%s %s' % (icmp_type, port_range_min))
            if port_range_max is not None:
                pf_rule.append('code %s' % port_range_max)

    def _ip_prefix_param(self, direction, ip_prefix, pf_rule):
        if ip_prefix != 'any':
            if '/' not in ip_prefix:
                # we need to convert it into a cidr
                ip_prefix = c_utils.ip_to_cidr(ip_prefix)
            elif ip_prefix.endswith('/0'):
                ip_prefix = 'any'
        direction = 'from' if direction == firewall.INGRESS_DIRECTION else 'to'
        pf_rule.append('%s %s' % (direction, ip_prefix))

    def _ip_prefix_port_param(self, direction, sg_rule, pf_rule):
        protocol = sg_rule.get('protocol')
        if direction == firewall.INGRESS_DIRECTION:
            ip_prefix = sg_rule.get('source_ip_prefix')
            ip_prefix = ip_prefix if ip_prefix else 'any'
            self._ip_prefix_param(direction, ip_prefix, pf_rule)
            self._port_param(protocol,
                             sg_rule.get('source_port_range_min'),
                             sg_rule.get('source_port_range_max'), pf_rule)
            self._ip_prefix_param(firewall.EGRESS_DIRECTION, 'any', pf_rule)
            self._port_param(protocol,
                             sg_rule.get('port_range_min'),
                             sg_rule.get('port_range_max'), pf_rule)
        else:
            self._ip_prefix_param(firewall.INGRESS_DIRECTION, 'any', pf_rule)
            self._port_param(protocol,
                             sg_rule.get('source_port_range_min'),
                             sg_rule.get('source_port_range_max'), pf_rule)

            ip_prefix = sg_rule.get('dest_ip_prefix')
            ip_prefix = ip_prefix if ip_prefix else 'any'
            self._ip_prefix_param(direction, ip_prefix, pf_rule)
            self._port_param(protocol,
                             sg_rule.get('port_range_min'),
                             sg_rule.get('port_range_max'), pf_rule)

    def _convert_sgr_to_pfr(self, device_name, direction,
                            security_group_rules):
        pf_rules = []
        for sg_rule in security_group_rules:
            pf_rule = ['pass']
            pf_rule.append("%s on %s" % (DIRECTION_PF_PARAM[direction],
                                         device_name))
            if sg_rule.get('ethertype') == constants.IPv6:
                pf_rule.append('inet6')
            else:
                pf_rule.append('inet')
            protocol = sg_rule.get('protocol')
            self._protocol_param(protocol, pf_rule)
            self._ip_prefix_port_param(direction, sg_rule, pf_rule)
            pf_rule.append('label "%s"' % self._get_label_number())
            pf_rules.append(' '.join(pf_rule))
        return pf_rules
