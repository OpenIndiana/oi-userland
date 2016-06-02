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

from oslo.config import cfg
from oslo_log import log as logging

from neutron.agent.linux import utils
from neutron.agent.linux import dhcp
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

    def _build_cmdline_callback(self, pid_file):
        cmd = [
            '/usr/lib/inet/dnsmasq',
            '--no-hosts',
            '--no-resolv',
            '--strict-order',
            '--bind-interfaces',
            '--interface=%s' % self.interface_name,
            '--except-interface=lo0',
            '--pid-file=%s' % pid_file,
            '--dhcp-hostsfile=%s' % self.get_conf_file_name('host'),
            '--addn-hosts=%s' % self.get_conf_file_name('addn_hosts'),
            '--dhcp-optsfile=%s' % self.get_conf_file_name('opts'),
            '--leasefile-ro',
            '--dhcp-authoritative'
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
            mtu = self.network.mtu
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

        return cmd

    def _release_lease(self, mac_address, ip):
        """Release a DHCP lease."""
        cmd = ['/usr/lib/inet/dhcp_release', self.interface_name,
               ip, mac_address]
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

    def setup_dhcp_port(self, network):
        """Create/update DHCP port for the host if needed and return port."""

        device_id = self.get_device_id(network)
        subnets = {}
        dhcp_enabled_subnet_ids = []
        for subnet in network.subnets:
            if subnet.enable_dhcp:
                dhcp_enabled_subnet_ids.append(subnet.id)
                subnets[subnet.id] = subnet

        dhcp_port = None
        for port in network.ports:
            port_device_id = getattr(port, 'device_id', None)
            port_device_owner = getattr(port, 'device_owner', None)

            # if the agent is started on a different node, then the
            # device_ids will be different since they are based off
            # hostname.
            if (port_device_id == device_id or
                    (port_device_owner == constants.DEVICE_OWNER_DHCP and
                     port_device_id.startswith('dhcp'))):
                port_fixed_ips = []
                for fixed_ip in port.fixed_ips:
                    port_fixed_ips.append({'subnet_id': fixed_ip.subnet_id,
                                           'ip_address': fixed_ip.ip_address})
                    if fixed_ip.subnet_id in dhcp_enabled_subnet_ids:
                        dhcp_enabled_subnet_ids.remove(fixed_ip.subnet_id)

                # If there are dhcp_enabled_subnet_ids here that means that
                # we need to add those to the port and call update.
                if dhcp_enabled_subnet_ids:
                    port_fixed_ips.extend(
                        [dict(subnet_id=s) for s in dhcp_enabled_subnet_ids])
                    dhcp_port = self.plugin.update_dhcp_port(
                        port.id, {'port': {'network_id': network.id,
                                           'fixed_ips': port_fixed_ips}})
                    if not dhcp_port:
                        raise exceptions.Conflict()
                else:
                    dhcp_port = port
                # break since we found port that matches device_id
                break

        # check for a reserved DHCP port
        if dhcp_port is None:
            LOG.debug('DHCP port %(device_id)s on network %(network_id)s'
                      ' does not yet exist. Checking for a reserved port.',
                      {'device_id': device_id, 'network_id': network.id})
            for port in network.ports:
                port_device_id = getattr(port, 'device_id', None)
                if port_device_id == constants.DEVICE_ID_RESERVED_DHCP_PORT:
                    dhcp_port = self.plugin.update_dhcp_port(
                        port.id, {'port': {'network_id': network.id,
                                           'device_id': device_id}})
                    if dhcp_port:
                        break

        # DHCP port has not yet been created.
        if dhcp_port is None:
            LOG.debug('DHCP port %(device_id)s on network %(network_id)s'
                      ' does not yet exist.', {'device_id': device_id,
                                               'network_id': network.id})
            port_dict = dict(
                name='',
                admin_state_up=True,
                device_id=device_id,
                network_id=network.id,
                tenant_id=network.tenant_id,
                fixed_ips=[dict(subnet_id=s) for s in dhcp_enabled_subnet_ids])
            dhcp_port = self.plugin.create_dhcp_port({'port': port_dict})

        if not dhcp_port:
            raise exceptions.Conflict()

        # Convert subnet_id to subnet dict
        fixed_ips = [dict(subnet_id=fixed_ip.subnet_id,
                          ip_address=fixed_ip.ip_address,
                          subnet=subnets[fixed_ip.subnet_id])
                     for fixed_ip in dhcp_port.fixed_ips]

        ips = [dhcp.DictModel(item) if isinstance(item, dict) else item
               for item in fixed_ips]
        dhcp_port.fixed_ips = ips

        return dhcp_port

    def setup(self, network):
        """Create and initialize a device for network's DHCP on this host."""
        port = self.setup_dhcp_port(network)
        interface_name = self.get_interface_name(network, port)

        if net_lib.Datalink.datalink_exists(interface_name):
            LOG.debug('Reusing existing device: %s.', interface_name)
        else:
            self.driver.plug(network.tenant_id, network.id,
                             port.id, interface_name, port.mac_address,
                             network=network,
                             vif_type=port['binding:vif_type'])
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

            self.driver.init_l3(interface_name, ip_cidrs, addrconf=addrconf)

        return interface_name

    def destroy(self, network, device_name):
        """Destroy the device used for the network's DHCP on this host."""

        self.driver.fini_l3(device_name)
        self.driver.unplug(device_name)
        self.plugin.release_dhcp_port(network.id,
                                      self.get_device_id(network))
