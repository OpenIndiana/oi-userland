# vim: tabstop=4 shiftwidth=4 softtabstop=4

# Copyright 2012 OpenStack Foundation
# All Rights Reserved.
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

import socket
import uuid

import netaddr
from oslo.config import cfg

from quantum.agent.common import config
from quantum.agent.linux import interface
from quantum.agent.linux import ip_lib
from quantum.common import exceptions
from quantum.openstack.common import importutils
from quantum.openstack.common import log as logging

LOG = logging.getLogger(__name__)
NS_PREFIX = 'qdhcp-'
METADATA_DEFAULT_PREFIX = 16
METADATA_DEFAULT_IP = '169.254.169.254/%d' % METADATA_DEFAULT_PREFIX


class DeviceManager(object):
    OPTS = [
        cfg.StrOpt('interface_driver',
                   help=_("The driver used to manage the virtual interface."))
    ]

    def __init__(self, conf, plugin):
        self.conf = conf
        self.root_helper = config.get_root_helper(conf)
        self.plugin = plugin
        cfg.CONF.register_opts(DeviceManager.OPTS)
        cfg.CONF.register_opts(interface.OPTS)
        if not conf.interface_driver:
            raise SystemExit(_('You must specify an interface driver'))
        try:
            self.driver = importutils.import_object(conf.interface_driver,
                                                    conf)
        except:
            msg = _("Error importing interface driver "
                    "'%s'") % conf.interface_driver
            raise SystemExit(msg)

    def get_interface_name(self, network, port=None):
        """Return interface(device) name for use by the DHCP process."""
        if not port:
            device_id = self.get_device_id(network)
            port = self.plugin.get_dhcp_port(network.id, device_id)
        return self.driver.get_device_name(port)

    def get_device_id(self, network):
        """Return a unique DHCP device ID for this host on the network."""
        # There could be more than one dhcp server per network, so create
        # a device id that combines host and network ids

        host_uuid = uuid.uuid5(uuid.NAMESPACE_DNS, socket.gethostname())
        return 'dhcp%s-%s' % (host_uuid, network.id)

    def _get_device(self, network):
        """Return DHCP ip_lib device for this host on the network."""
        device_id = self.get_device_id(network)
        port = self.plugin.get_dhcp_port(network.id, device_id)
        interface_name = self.get_interface_name(network, port)
        namespace = NS_PREFIX + network.id
        return ip_lib.IPDevice(interface_name,
                               self.root_helper,
                               namespace)

    def _set_default_route(self, network):
        """Sets the default gateway for this dhcp namespace.

        This method is idempotent and will only adjust the route if adjusting
        it would change it from what it already is.  This makes it safe to call
        and avoids unnecessary perturbation of the system.
        """
        device = self._get_device(network)
        gateway = device.route.get_gateway()

        for subnet in network.subnets:
            skip_subnet = (
                subnet.ip_version != 4
                or not subnet.enable_dhcp
                or subnet.gateway_ip is None)

            if skip_subnet:
                continue

            if gateway != subnet.gateway_ip:
                m = _('Setting gateway for dhcp netns on net %(n)s to %(ip)s')
                LOG.debug(m, {'n': network.id, 'ip': subnet.gateway_ip})

                device.route.add_gateway(subnet.gateway_ip)

            return

        # No subnets on the network have a valid gateway.  Clean it up to avoid
        # confusion from seeing an invalid gateway here.
        if gateway is not None:
            msg = _('Removing gateway for dhcp netns on net %s')
            LOG.debug(msg, network.id)

            device.route.delete_gateway(gateway)

    def setup(self, network, reuse_existing=False):
        """Create and initialize a device for network's DHCP on this host."""
        device_id = self.get_device_id(network)
        port = self.plugin.get_dhcp_port(network.id, device_id)

        interface_name = self.get_interface_name(network, port)

        if self.conf.use_namespaces:
            namespace = NS_PREFIX + network.id
        else:
            namespace = None

        if ip_lib.device_exists(interface_name,
                                self.root_helper,
                                namespace):
            if not reuse_existing:
                raise exceptions.PreexistingDeviceFailure(
                    dev_name=interface_name)

            LOG.debug(_('Reusing existing device: %s.'), interface_name)
        else:
            self.driver.plug(network.id,
                             port.id,
                             interface_name,
                             port.mac_address,
                             namespace=namespace)
        ip_cidrs = []
        for fixed_ip in port.fixed_ips:
            subnet = fixed_ip.subnet
            net = netaddr.IPNetwork(subnet.cidr)
            ip_cidr = '%s/%s' % (fixed_ip.ip_address, net.prefixlen)
            ip_cidrs.append(ip_cidr)

        if (self.conf.enable_isolated_metadata and
            self.conf.use_namespaces):
            ip_cidrs.append(METADATA_DEFAULT_IP)

        self.driver.init_l3(interface_name, ip_cidrs,
                            namespace=namespace)

        # ensure that the dhcp interface is first in the list
        if namespace is None:
            device = ip_lib.IPDevice(interface_name,
                                     self.root_helper)
            device.route.pullup_route(interface_name)

        if self.conf.enable_metadata_network:
            meta_cidr = netaddr.IPNetwork(METADATA_DEFAULT_IP)
            metadata_subnets = [s for s in network.subnets if
                                netaddr.IPNetwork(s.cidr) in meta_cidr]
            if metadata_subnets:
                # Add a gateway so that packets can be routed back to VMs
                device = ip_lib.IPDevice(interface_name,
                                         self.root_helper,
                                         namespace)
                # Only 1 subnet on metadata access network
                gateway_ip = metadata_subnets[0].gateway_ip
                device.route.add_gateway(gateway_ip)
        elif self.conf.use_namespaces:
            self._set_default_route(network)

        return interface_name

    def update(self, network):
        """Update device settings for the network's DHCP on this host."""
        if self.conf.use_namespaces and not self.conf.enable_metadata_network:
            self._set_default_route(network)

    def destroy(self, network, device_name):
        """Destroy the device used for the network's DHCP on this host."""
        if self.conf.use_namespaces:
            namespace = NS_PREFIX + network.id
        else:
            namespace = None

        self.driver.unplug(device_name, namespace=namespace)

        self.plugin.release_dhcp_port(network.id,
                                      self.get_device_id(network))
