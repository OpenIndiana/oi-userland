# vim: tabstop=4 shiftwidth=4 softtabstop=4

# Copyright 2012 OpenStack Foundation
# All Rights Reserved.
#
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
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

import abc
import netaddr
import os

from oslo_config import cfg
from oslo_log import log as logging
from oslo_utils import excutils

from neutron._i18n import _, _LI, _LW, _LE
from neutron.agent.linux import dhcp
from neutron.agent.linux import utils
from neutron.agent.solaris import net_lib
from neutron.common import constants
from neutron.common import exceptions
from neutron.common import ipv6_utils

LOG = logging.getLogger(__name__)


class Dnsmasq(dhcp.Dnsmasq):
    """ Wrapper around Linux implementation of Dnsmasq."""

    def __init__(self, conf, network, process_monitor, version=None,
                 plugin=None):
        super(Dnsmasq, self).__init__(conf, network, process_monitor,
                                      version, plugin)
        self.device_manager = DeviceManager(self.conf, plugin)

    # overrides method in DhcpLocalProcess due to no namespace support
    def _destroy_namespace_and_port(self):
        try:
            self.device_manager.destroy(self.network, self.interface_name)
        except RuntimeError:
            LOG.warning(_LW('Failed trying to delete interface: %s'),
                        self.interface_name)

    def _build_cmdline_callback(self, pid_file):
        # We ignore local resolv.conf if dns servers are specified
        # or if local resolution is explicitly disabled.
        _no_resolv = (
            '--no-resolv' if self.conf.dnsmasq_dns_servers or
            not self.conf.dnsmasq_local_resolv else '')
        cmd = [
            '/usr/lib/inet/dnsmasq',
            '--no-hosts',
            _no_resolv,
            '--strict-order',
            '--bind-interfaces',
            '--interface=%s' % self.interface_name,
            '--except-interface=lo0',
            '--pid-file=%s' % pid_file,
            '--dhcp-hostsfile=%s' % self.get_conf_file_name('host'),
            '--addn-hosts=%s' % self.get_conf_file_name('addn_hosts'),
            '--dhcp-optsfile=%s' % self.get_conf_file_name('opts'),
            '--dhcp-leasefile=%s' % self.get_conf_file_name('leases'),
            '--dhcp-match=set:ipxe,175',
        ]

        possible_leases = 0
        for i, subnet in enumerate(self.network.subnets):
            mode = None
            # if a subnet is specified to have dhcp disabled
            if not subnet.enable_dhcp:
                continue
            if subnet.ip_version == 4:
                mode = 'static'
            else:
                # We need to also set the DUID for the DHCPv6 server to use
                macaddr_cmd = ['/usr/sbin/dladm', 'show-linkprop',
                               '-co', 'value', '-p', 'mac-address',
                               self.interface_name]
                stdout = utils.execute(macaddr_cmd)
                uid = stdout.splitlines()[0].strip()
                # format the MAC address
                uid = ':'.join(['%.2x' % w for w in netaddr.EUI(uid).words])
                # IANA assigned ID for Oracle
                enterprise_id = '111'
                cmd.append('--dhcp-duid=%s,%s' % (enterprise_id, uid))

                # Note(scollins) If the IPv6 attributes are not set, set it as
                # static to preserve previous behavior
                addr_mode = getattr(subnet, 'ipv6_address_mode', None)
                ra_mode = getattr(subnet, 'ipv6_ra_mode', None)
                if (addr_mode in [constants.DHCPV6_STATEFUL,
                                  constants.DHCPV6_STATELESS] or
                        not addr_mode and not ra_mode):
                    mode = 'static'

            cidr = netaddr.IPNetwork(subnet.cidr)

            if self.conf.dhcp_lease_duration == -1:
                lease = 'infinite'
            else:
                lease = '%ss' % self.conf.dhcp_lease_duration

            # mode is optional and is not set - skip it
            if mode:
                if subnet.ip_version == 4:
                    cmd.append('--dhcp-range=%s%s,%s,%s,%s' %
                               ('set:', self._TAG_PREFIX % i,
                                cidr.network, mode, lease))
                else:
                    cmd.append('--dhcp-range=%s%s,%s,%s,%d,%s' %
                               ('set:', self._TAG_PREFIX % i,
                                cidr.network, mode,
                                cidr.prefixlen, lease))
                possible_leases += cidr.size

        if cfg.CONF.advertise_mtu:
            mtu = getattr(self.network, 'mtu', 0)
            # Do not advertise unknown mtu
            if mtu > 0:
                cmd.append('--dhcp-option-force=option:mtu,%d' % mtu)

        # Cap the limit because creating lots of subnets can inflate
        # this possible lease cap.
        cmd.append('--dhcp-lease-max=%d' %
                   min(possible_leases, self.conf.dnsmasq_lease_max))

        cmd.append('--conf-file=%s' % self.conf.dnsmasq_config_file)
        if self.conf.dnsmasq_dns_servers:
            cmd.extend(
                '--server=%s' % server
                for server in self.conf.dnsmasq_dns_servers)

        if self.conf.dhcp_domain:
            cmd.append('--domain=%s' % self.conf.dhcp_domain)

        if self.conf.dhcp_broadcast_reply:
            cmd.append('--dhcp-broadcast')

        if self.conf.dnsmasq_base_log_dir:
            log_dir = os.path.join(
                self.conf.dnsmasq_base_log_dir,
                self.network.id)
            try:
                if not os.path.exists(log_dir):
                    os.makedirs(log_dir)
            except OSError:
                LOG.error(_LE('Error while create dnsmasq log dir: %s'),
                          log_dir)
            else:
                log_filename = os.path.join(log_dir, 'dhcp_dns_log')
                cmd.append('--log-queries')
                cmd.append('--log-dhcp')
                cmd.append('--log-facility=%s' % log_filename)

        return cmd

    def _release_lease(self, mac_address, ip, client_id):
        """Release a DHCP lease."""
        if netaddr.IPAddress(ip).version == constants.IP_VERSION_6:
            # Note(SridharG) dhcp_release is only supported for IPv4
            # addresses. For more details, please refer to man page.
            return

        cmd = ['/usr/lib/inet/dhcp_release', self.interface_name,
               ip, mac_address]
        if client_id:
            cmd.append(client_id)
        utils.execute(cmd)

    def _make_subnet_interface_ip_map(self):
        # TODO(gmoodalb): need to complete this when we support metadata
        # in neutron-dhcp-agent as-well for isolated subnets
        pass

    @classmethod
    def should_enable_metadata(cls, conf, network):
        # TODO(gmoodalb): need to complete this when we support metadata
        # in neutron-dhcp-agent as-well for isolated subnets
        return False


class DeviceManager(dhcp.DeviceManager):

    def __init__(self, conf, plugin):
        super(DeviceManager, self).__init__(conf, plugin)

    def _set_default_route(self, network, device_name):
        """Sets the default gateway for this dhcp namespace.

        This method is idempotent and will only adjust the route if adjusting
        it would change it from what it already is.  This makes it safe to call
        and avoids unnecessary perturbation of the system.
        """
        pass

    def _setup_existing_dhcp_port(self, network, device_id, dhcp_subnets):
        """Set up the existing DHCP port, if there is one."""

        # To avoid pylint thinking that port might be undefined after
        # the following loop...
        port = None

        # Look for an existing DHCP port for this network.
        for port in network.ports:
            port_device_id = getattr(port, 'device_id', None)
            port_device_owner = getattr(port, 'device_owner', None)
            if (port_device_id == device_id or
                (port_device_owner == constants.DEVICE_OWNER_DHCP and
                 port_device_id.startswith('dhcp'))):
                # If using gateway IPs on this port, we can skip the
                # following code, whose purpose is just to review and
                # update the Neutron-allocated IP addresses for the
                # port.
                if self.driver.use_gateway_ips:
                    return port
                # Otherwise break out, as we now have the DHCP port
                # whose subnets and addresses we need to review.
                break
        else:
            return None

        # Compare what the subnets should be against what is already
        # on the port.
        dhcp_enabled_subnet_ids = set(dhcp_subnets)
        port_subnet_ids = set(ip.subnet_id for ip in port.fixed_ips)

        # If those differ, we need to call update.
        if dhcp_enabled_subnet_ids != port_subnet_ids:
            # Collect the subnets and fixed IPs that the port already
            # has, for subnets that are still in the DHCP-enabled set.
            wanted_fixed_ips = []
            for fixed_ip in port.fixed_ips:
                if fixed_ip.subnet_id in dhcp_enabled_subnet_ids:
                    wanted_fixed_ips.append(
                        {'subnet_id': fixed_ip.subnet_id,
                         'ip_address': fixed_ip.ip_address})

            # Add subnet IDs for new DHCP-enabled subnets.
            wanted_fixed_ips.extend(
                dict(subnet_id=s)
                for s in dhcp_enabled_subnet_ids - port_subnet_ids)

            # Update the port to have the calculated subnets and fixed
            # IPs.  The Neutron server will allocate a fresh IP for
            # each subnet that doesn't already have one.
            port = self.plugin.update_dhcp_port(
                port.id,
                {'port': {'network_id': network.id,
                          'fixed_ips': wanted_fixed_ips}})
            if not port:
                raise exceptions.Conflict()

        return port

    def setup(self, network):
        """Create and initialize a device for network's DHCP on this host."""
        port = self.setup_dhcp_port(network)
        self._update_dhcp_port(network, port)
        interface_name = self.get_interface_name(network, port)

        if net_lib.Datalink.datalink_exists(interface_name):
            LOG.debug('Reusing existing device: %s.', interface_name)
        else:
            try:
                self.driver.plug(network.tenant_id, network.id,
                                 port.id, interface_name, port.mac_address,
                                 network=network, mtu=network.get('mtu'),
                                 vif_type=getattr(port, 'binding:vif_type',
                                                  None))
            except Exception:
                with excutils.save_and_reraise_exception():
                    LOG.exception(_LE('Unable to plug DHCP port for '
                                      'network %s. Releasing port.'),
                                  network.id)
                    self.plugin.release_dhcp_port(network.id, port.device_id)
        ip_cidrs = []
        addrconf = False
        for fixed_ip in port.fixed_ips:
            subnet = fixed_ip.subnet
            if not ipv6_utils.is_auto_address_subnet(subnet):
                net = netaddr.IPNetwork(subnet.cidr)
                ip_cidr = '%s/%s' % (fixed_ip.ip_address, net.prefixlen)
                ip_cidrs.append(ip_cidr)
            else:
                addrconf = True

        if self.driver.use_gateway_ips:
            # For each DHCP-enabled subnet, add that subnet's gateway
            # IP address to the Linux device for the DHCP port.
            for subnet in network.subnets:
                if not subnet.enable_dhcp:
                    continue
                gateway = subnet.gateway_ip
                if gateway:
                    net = netaddr.IPNetwork(subnet.cidr)
                    ip_cidrs.append('%s/%s' % (gateway, net.prefixlen))

        self.driver.init_l3(interface_name, ip_cidrs, addrconf=addrconf)

        return interface_name
