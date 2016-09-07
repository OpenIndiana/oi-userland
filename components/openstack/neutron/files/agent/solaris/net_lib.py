# vim: tabstop=4 shiftwidth=4 softtabstop=4

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
# @author: Girish Moodalbail, Oracle, Inc.
#

import eventlet
import netaddr

from oslo_log import log as logging

from neutron.agent.linux import utils
from neutron.i18n import _LE

LOG = logging.getLogger(__name__)


class CommandBase(object):
    @classmethod
    def execute_with_pfexec(cls, cmd, **kwargs):
        # uses pfexec
        cmd.insert(0, '/usr/bin/pfexec')
        return utils.execute(cmd, **kwargs)

    @classmethod
    def execute(cls, cmd, **kwargs):
        return utils.execute(cmd, **kwargs)


class IPInterface(CommandBase):
    '''Wrapper around Solaris ipadm(1m) command.'''

    def __init__(self, ifname):
        self._ifname = ifname

    @classmethod
    def ifname_exists(cls, ifname):
        try:
            cmd = ['/usr/sbin/ipadm', 'show-if', '-po', 'ifname', ifname]
            cls.execute(cmd, log_fail_as_error=False)
        except Exception:
            return False
        return True

    @classmethod
    def ipaddr_exists(cls, ipaddr, ifname=None):
        cmd = ['/usr/sbin/ipadm', 'show-addr', '-po', 'addr']
        if ifname:
            cmd.append(ifname)
        stdout = cls.execute(cmd)

        return ipaddr in stdout

    def ipaddr_list(self, filters=None):
        cmd = ['/usr/sbin/ipadm', 'show-addr', '-po', 'type,addr',
               self._ifname]
        stdout = self.execute(cmd)
        atype_addrs = stdout.strip().split('\n')
        result = {}
        for atype_addr in atype_addrs:
            atype, addr = atype_addr.split(':', 1)
            val = result.get(atype)
            if val is None:
                result[atype] = []
                val = result.get(atype)
            # in the case of IPv6 addresses remove any escape '\' character
            val.append(addr.replace("\\", ""))
        return result

    def create_address(self, ipaddr, addrobjname=None, temp=True,
                       ifcheck=True, addrcheck=True):
        if ifcheck and not self.ifname_exists(self._ifname):
            # create ip interface
            cmd = ['/usr/sbin/ipadm', 'create-ip', self._ifname]
            if temp:
                cmd.append('-t')
            self.execute_with_pfexec(cmd)
        elif addrcheck and self.ipaddr_exists(ipaddr, self._ifname):
            return

        # If an address is IPv6, then to create a static IPv6 address
        # we need to create link-local address first
        if netaddr.IPNetwork(ipaddr).version == 6:
            # check if link-local address already exists
            cmd = ['/usr/sbin/dladm', 'show-linkprop', '-co', 'value',
                   '-p', 'mac-address', self._ifname]
            stdout = self.execute(cmd)
            mac_addr = stdout.splitlines()[0].strip()
            ll_addr = netaddr.EUI(mac_addr).ipv6_link_local()

            if addrcheck and not self.ipaddr_exists(str(ll_addr),
                                                    self._ifname):
                # create a link-local address
                cmd = ['/usr/sbin/ipadm', 'create-addr', '-T', 'static', '-a',
                       str(ll_addr), self._ifname]
                if temp:
                    cmd.append('-t')
                self.execute_with_pfexec(cmd)

        cmd = ['/usr/sbin/ipadm', 'create-addr', '-T', 'static', '-a',
               ipaddr, self._ifname]
        if temp:
            cmd.append('-t')

        self.execute_with_pfexec(cmd)

    def create_addrconf(self, temp=True):
        if not self.ifname_exists(self._ifname):
            # create ip interface
            cmd = ['/usr/sbin/ipadm', 'create-ip', self._ifname]
            if temp:
                cmd.append('-t')
            self.execute_with_pfexec(cmd)
        else:
            cmd = ['/usr/sbin/ipadm', 'show-addr', '-po', 'type', self._ifname]
            stdout = self.execute(cmd)
            if 'addrconf' in stdout:
                return

        cmd = ['/usr/sbin/ipadm', 'create-addr', '-T', 'addrconf',
               self._ifname]
        if temp:
            cmd.append('-t')
        self.execute_with_pfexec(cmd)

    def delete_address(self, ipaddr, addrcheck=True):
        if addrcheck and not self.ipaddr_exists(ipaddr, self._ifname):
            return

        cmd = ['/usr/sbin/ipadm', 'show-addr', '-po', 'addrobj,addr',
               self._ifname]
        stdout = self.execute(cmd)
        aobj_addrs = stdout.strip().split('\n')
        for aobj_addr in aobj_addrs:
            if ipaddr not in aobj_addr:
                continue
            aobj = aobj_addr.split(':')[0]
            cmd = ['/usr/sbin/ipadm', 'delete-addr', aobj]
            self.execute_with_pfexec(cmd)
            break

        isV6 = netaddr.IPNetwork(ipaddr).version == 6
        if len(aobj_addrs) == 1 or (isV6 and len(aobj_addrs) == 2):
            # delete the interface as well
            cmd = ['/usr/sbin/ipadm', 'delete-ip', self._ifname]
            self.execute_with_pfexec(cmd)

    def delete_ip(self):
        if not self.ifname_exists(self._ifname):
            return

        cmd = ['/usr/sbin/ipadm', 'delete-ip', self._ifname]
        self.execute_with_pfexec(cmd)


class Datalink(CommandBase):
    '''Wrapper around Solaris dladm(1m) command.'''

    def __init__(self, dlname):
        self._dlname = dlname

    @classmethod
    def datalink_exists(cls, dlname):
        try:
            cmd = ['/usr/sbin/dladm', 'show-link', '-po', 'link', dlname]
            utils.execute(cmd, log_fail_as_error=False)
        except Exception:
            return False
        return True

    def create_vnic(self, lower_link, mac_address=None, vid=None, temp=True):
        if self.datalink_exists(self._dlname):
            return

        if vid:
            # If the default_tag of lower_link is same as vid, then there
            # is no need to set vid
            cmd = ['/usr/sbin/dladm', 'show-linkprop', '-co', 'value',
                   '-p', 'default_tag', lower_link]
            stdout = utils.execute(cmd)
            default_tag = stdout.splitlines()[0].strip()
            if default_tag == vid or (vid == '1' and default_tag == '0'):
                vid = '0'
        else:
            vid = '0'
        cmd = ['/usr/sbin/dladm', 'create-vnic', '-l', lower_link,
               '-m', mac_address, '-v', vid, self._dlname]
        if temp:
            cmd.append('-t')

        self.execute_with_pfexec(cmd)

    def delete_vnic(self):
        if not self.datalink_exists(self._dlname):
            return

        cmd = ['/usr/sbin/dladm', 'delete-vnic', self._dlname]
        self.execute_with_pfexec(cmd)

    @classmethod
    def show_link(cls):
        cmd = ['/usr/sbin/dladm', 'show-link', '-po', 'link']
        stdout = utils.execute(cmd)

        return stdout.splitlines()


def _arping(iface_name, address, count):
    # Set timeout with -w to ensure arping exits in case the interface
    # is deleted while it is running
    arping_cmd = ['/usr/sbin/arping', '-A', '-I', iface_name, '-c', count,
                  '-w', 2 * count, address]
    try:
        utils.execute(arping_cmd, check_exit_code=False)
    except Exception:
        msg = _LE("Failed sending gratuitous ARP to %(addr)s on "
                  "an interface %(iface)s")
        LOG.exception(msg, {'addr': address, 'iface': iface_name})


def send_ip_addr_adv_notif(iface_name, address, config):
    """Send advance notification of an IP address assignment.

    If the address is in the IPv4 family, send gratuitous ARP.

    If the address is in the IPv6 family, no advance notification is
    necessary, since the Neighbor Discovery Protocol (NDP), Duplicate
    Address Discovery (DAD), and (for stateless addresses) router
    advertisements (RAs) are sufficient for address resolution and
    duplicate address detection.
    """
    count = config.send_arp_for_ha

    def arping():
        _arping(iface_name, address, count)

    if count > 0 and netaddr.IPAddress(address).version == 4:
        eventlet.spawn_n(arping)
