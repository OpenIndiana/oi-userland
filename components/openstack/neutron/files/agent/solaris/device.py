# vim: tabstop=4 shiftwidth=4 softtabstop=4

# Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved.
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
# @author: Girish Moodalbail, Oracle, Inc.

import socket
import uuid

import netaddr

from oslo.config import cfg
from quantum.agent.common import config
from quantum.agent.solaris import interface
from quantum.openstack.common import importutils
from quantum.openstack.common import log as logging

LOG = logging.getLogger(__name__)


class DeviceManager(object):
    OPTS = [
        cfg.StrOpt('interface_driver',
                   help=_('The driver used to manage the virtual interface.'))
    ]

    def __init__(self, conf, plugin):
        self.conf = conf
        self.root_helper = config.get_root_helper(conf)
        self.plugin = plugin
        cfg.CONF.register_opts(DeviceManager.OPTS)
        cfg.CONF.register_opts(interface.OPTS)
        if not conf.interface_driver:
            raise SystemExit(_('You must specify an interface driver.'))
        try:
            self.driver = importutils.import_object(conf.interface_driver,
                                                    conf)
        except ImportError as ie:
            raise SystemExit(_('Error importing interface driver %s: %s')
                             % (conf.interface_driver, ie))

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

    def setup(self, network, reuse_existing=False):
        """Create and initialize a device for network's DHCP on this host."""
        device_id = self.get_device_id(network)
        port = self.plugin.get_dhcp_port(network.id, device_id)

        interface_name = self.get_interface_name(network, port)

        self.driver.plug(network.tenant_id, network.id, port.id,
                         interface_name)
        ip_cidrs = []
        for fixed_ip in port.fixed_ips:
            subnet = fixed_ip.subnet
            net = netaddr.IPNetwork(subnet.cidr)
            ip_cidr = '%s/%s' % (fixed_ip.ip_address, net.prefixlen)
            ip_cidrs.append(ip_cidr)

        self.driver.init_l3(interface_name, ip_cidrs)

        return interface_name

    def update(self, network):
        """Update device settings for the network's DHCP on this host."""
        pass

    def destroy(self, network, device_name):
        """Destroy the device used for the network's DHCP on this host."""

        self.driver.fini_l3(device_name)
        self.driver.unplug(device_name)
        self.plugin.release_dhcp_port(network.id,
                                      self.get_device_id(network))
