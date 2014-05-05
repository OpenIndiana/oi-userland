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

import abc
import os
import re
import shutil
import StringIO

import netaddr

from oslo.config import cfg
from quantum.agent.linux import utils
from quantum.openstack.common import log as logging
from quantum.openstack.common import uuidutils

LOG = logging.getLogger(__name__)

OPTS = [
    cfg.StrOpt('dhcp_confs',
               default='$state_path/dhcp',
               help=_('Location to store DHCP server config files')),
    cfg.IntOpt('dhcp_lease_time',
               default=120,
               help=_('Lifetime of a DHCP lease in seconds')),
    cfg.StrOpt('dhcp_domain',
               default='openstacklocal',
               help=_('Domain to use for building the hostnames')),
    cfg.StrOpt('dnsmasq_config_file',
               default='',
               help=_('Override the default dnsmasq settings with this file')),
    cfg.StrOpt('dnsmasq_dns_server',
               help=_('Use another DNS server before any in '
                      '/etc/resolv.conf.')),
]

IPV4 = 4
IPV6 = 6
UDP = 'udp'
TCP = 'tcp'
DNS_PORT = 53
DHCPV4_PORT = 67
DHCPV6_PORT = 467


class DhcpBase(object):
    __metaclass__ = abc.ABCMeta

    def __init__(self, conf, network, root_helper='sudo',
                 device_delegate=None, namespace=None, version=None):
        self.conf = conf
        self.network = network
        self.root_helper = root_helper
        self.device_delegate = device_delegate
        self.namespace = namespace
        self.version = version

    @abc.abstractmethod
    def enable(self):
        """Enables DHCP for this network."""

    @abc.abstractmethod
    def disable(self, retain_port=False):
        """Disable dhcp for this network."""

    def restart(self):
        """Restart the dhcp service for the network."""
        self.disable(retain_port=True)
        self.enable()

    @abc.abstractproperty
    def active(self):
        """Boolean representing the running state of the DHCP server."""

    @abc.abstractmethod
    def reload_allocations(self):
        """Force the DHCP server to reload the assignment database."""

    @classmethod
    def existing_dhcp_networks(cls, conf, root_helper):
        """Return a list of existing networks ids (ones we have configs for)"""

        raise NotImplementedError

    @classmethod
    def check_version(cls):
        """Execute version checks on DHCP server."""

        raise NotImplementedError


class DhcpLocalProcess(DhcpBase):
    PORTS = []

    def _enable_dhcp(self):
        """check if there is a subnet within the network with dhcp enabled."""
        return any(s for s in self.network.subnets if s.enable_dhcp)

    def enable(self):
        """Enables DHCP for this network by spawning a local process."""
        interface_name = self.device_delegate.setup(self.network,
                                                    reuse_existing=True)
        if self.active:
            self.restart()
        elif self._enable_dhcp():
            self.interface_name = interface_name
            self.spawn_process()

    def disable(self, retain_port=False):
        """Disable DHCP for this network by killing the local process."""
        pid = self.pid

        if self.active:
            cmd = ['kill', '-9', pid]
            utils.execute(cmd)

            if not retain_port:
                self.device_delegate.destroy(self.network, self.interface_name)

        elif pid:
            LOG.debug(_('DHCP for %(net_id)s pid %(pid)d is stale, ignoring '
                        'command'), {'net_id': self.network.id, 'pid': pid})
        else:
            LOG.debug(_('No DHCP started for %s'), self.network.id)

        self._remove_config_files()

    def _remove_config_files(self):
        confs_dir = os.path.abspath(os.path.normpath(self.conf.dhcp_confs))
        conf_dir = os.path.join(confs_dir, self.network.id)
        shutil.rmtree(conf_dir, ignore_errors=True)

    def get_conf_file_name(self, kind, ensure_conf_dir=False):
        """Returns the file name for a given kind of config file."""
        confs_dir = os.path.abspath(os.path.normpath(self.conf.dhcp_confs))
        conf_dir = os.path.join(confs_dir, self.network.id)
        if ensure_conf_dir:
            if not os.path.isdir(conf_dir):
                os.makedirs(conf_dir, 0755)

        return os.path.join(conf_dir, kind)

    def _get_value_from_conf_file(self, kind, converter=None):
        """A helper function to read a value from one of the state files."""
        file_name = self.get_conf_file_name(kind)
        msg = _('Error while reading %s')

        try:
            with open(file_name, 'r') as f:
                try:
                    return converter and converter(f.read()) or f.read()
                except ValueError, e:
                    msg = _('Unable to convert value in %s')
        except IOError, e:
            msg = _('Unable to access %s')

        LOG.debug(msg % file_name)
        return None

    @property
    def pid(self):
        """Last known pid for the DHCP process spawned for this network."""
        return self._get_value_from_conf_file('pid', int)

    @property
    def active(self):
        pid = self.pid
        if pid is None:
            return False

        cmd = ['pargs', pid]
        try:
            return self.network.id in utils.execute(cmd)
        except RuntimeError:
            return False

    @property
    def interface_name(self):
        return self._get_value_from_conf_file('interface')

    @interface_name.setter
    def interface_name(self, value):
        interface_file_path = self.get_conf_file_name('interface',
                                                      ensure_conf_dir=True)
        utils.replace_file(interface_file_path, value)

    @abc.abstractmethod
    def spawn_process(self):
        pass


class Dnsmasq(DhcpLocalProcess):
    # The ports that need to be opened when security policies are active
    # on the Quantum port used for DHCP.  These are provided as a convenience
    # for users of this class.
    PORTS = {IPV4: [(UDP, DNS_PORT), (TCP, DNS_PORT), (UDP, DHCPV4_PORT)],
             IPV6: [(UDP, DNS_PORT), (TCP, DNS_PORT), (UDP, DHCPV6_PORT)]}

    _TAG_PREFIX = 'tag%d'

    QUANTUM_NETWORK_ID_KEY = 'QUANTUM_NETWORK_ID'
    QUANTUM_RELAY_SOCKET_PATH_KEY = 'QUANTUM_RELAY_SOCKET_PATH'

    @classmethod
    def check_version(cls):
        # For Solaris, we rely on the packaging system to ensure a
        # matching/supported version of dnsmasq
        pass

    @classmethod
    def existing_dhcp_networks(cls, conf, root_helper):
        """Return a list of existing networks ids (ones we have configs for)"""

        confs_dir = os.path.abspath(os.path.normpath(conf.dhcp_confs))

        class FakeNetwork:
            def __init__(self, net_id):
                self.id = net_id

        return [
            c for c in os.listdir(confs_dir)
            if (uuidutils.is_uuid_like(c) and
                cls(conf, FakeNetwork(c), root_helper).active)
        ]

    def spawn_process(self):
        """Spawns a Dnsmasq process for the network."""
        env = {
            self.QUANTUM_NETWORK_ID_KEY: self.network.id
        }

        cmd = [
            '/usr/lib/inet/dnsmasq',
            '--no-hosts',
            '--no-resolv',
            '--strict-order',
            '--bind-interfaces',
            '--interface=%s' % self.interface_name,
            '--except-interface=lo0',
            '--pid-file=%s' % self.get_conf_file_name(
                'pid', ensure_conf_dir=True),
            # TODO(gmoodalb): calculate value from cidr (defaults to 150)
            # '--dhcp-lease-max=%s' % ?,
            '--dhcp-hostsfile=%s' % self._output_hosts_file(),
            '--dhcp-optsfile=%s' % self._output_opts_file(),
            # '--dhcp-script=%s' % self._lease_relay_script_path(),
            '--leasefile-ro',
        ]

        for i, subnet in enumerate(self.network.subnets):
            # if a subnet is specified to have dhcp disabled
            if not subnet.enable_dhcp:
                continue
            if subnet.ip_version == 4:
                mode = 'static'
            else:
                # TODO(gmoodalb): how do we indicate other options
                # ra-only, slaac, ra-nameservers, and ra-stateless.
                # We need to also set the DUID for DHCPv6 server to use
                macaddr_cmd = ['/usr/sbin/dladm', 'show-linkprop',
                               '-co', 'value', '-p', 'mac-address',
                               self.interface_name]
                stdout = utils.execute(macaddr_cmd)
                uid = stdout.splitlines()[0].strip()
                # IANA assigned ID for Oracle
                enterprise_id = '111'
                cmd.append('--dhcp-duid=%s,%s' % (enterprise_id, uid))
                mode = 'static'
            cmd.append('--dhcp-range=set:%s,%s,%s,%ss' %
                       (self._TAG_PREFIX % i,
                        netaddr.IPNetwork(subnet.cidr).network,
                        mode, self.conf.dhcp_lease_time))

        cmd.append('--conf-file=%s' % self.conf.dnsmasq_config_file)
        if self.conf.dnsmasq_dns_server:
            cmd.append('--server=%s' % self.conf.dnsmasq_dns_server)

        if self.conf.dhcp_domain:
            cmd.append('--domain=%s' % self.conf.dhcp_domain)
        utils.execute(cmd)

    def reload_allocations(self):
        """Rebuild the dnsmasq config and signal the dnsmasq to reload."""

        # If all subnets turn off dhcp, kill the process.
        if not self._enable_dhcp():
            self.disable()
            LOG.debug(_('Killing dhcpmasq for network since all subnets have '
                        'turned off DHCP: %s'), self.network.id)
            return

        self._output_hosts_file()
        self._output_opts_file()

        if self.active:
            cmd = ['kill', '-HUP', self.pid]
            utils.execute(cmd)
        else:
            LOG.debug(_('Pid %d is stale, relaunching dnsmasq'), self.pid)
        LOG.debug(_('Reloading allocations for network: %s'), self.network.id)

    def _output_hosts_file(self):
        """Writes a dnsmasq compatible hosts file."""
        r = re.compile('[:.]')
        buf = StringIO.StringIO()

        for port in self.network.ports:
            for alloc in port.fixed_ips:
                name = 'host-%s.%s' % (r.sub('-', alloc.ip_address),
                                       self.conf.dhcp_domain)
                buf.write('%s,%s,%s\n' %
                          (port.mac_address, name, alloc.ip_address))

        name = self.get_conf_file_name('host')
        utils.replace_file(name, buf.getvalue())
        return name

    def _output_opts_file(self):
        """Write a dnsmasq compatible options file."""

        options = []
        for i, subnet in enumerate(self.network.subnets):
            if not subnet.enable_dhcp:
                continue
            if subnet.dns_nameservers:
                options.append(
                    self._format_option(i, 'dns-server',
                                        ','.join(subnet.dns_nameservers)))

            host_routes = ["%s,%s" % (hr.destination, hr.nexthop)
                           for hr in subnet.host_routes]

            if host_routes:
                options.append(
                    self._format_option(i, 'classless-static-route',
                                        ','.join(host_routes)))

            if subnet.ip_version == 4:
                if subnet.gateway_ip:
                    options.append(self._format_option(i, 'router',
                                                       subnet.gateway_ip))
                else:
                    options.append(self._format_option(i, 'router'))

        name = self.get_conf_file_name('opts')
        utils.replace_file(name, '\n'.join(options))
        return name

    def _format_option(self, index, option_name, *args):
        return ','.join(('tag:' + self._TAG_PREFIX % index,
                         'option:%s' % option_name) + args)

    @classmethod
    def lease_update(cls):
        pass
