# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
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


import rad.client as radcli
import rad.connect as radcon
import rad.bindings.com.oracle.solaris.rad.evscntl_1 as evsbind

from oslo_config import cfg
from oslo_log import log as logging

from neutron.agent.linux import utils
from neutron.agent.solaris import net_lib
from neutron.common import exceptions


LOG = logging.getLogger(__name__)

OPTS = [
    cfg.StrOpt('evs_controller', default='ssh://evsuser@localhost',
               help=_("An URI that specifies an EVS controller"))
]


class EVSControllerError(exceptions.NeutronException):
    message = _("EVS controller: %(errmsg)s")

    def __init__(self, evs_errmsg):
        super(EVSControllerError, self).__init__(errmsg=evs_errmsg)


class SolarisVNICDriver(object):
    """Driver used to manage Solaris EVS VNICs.

    This class provides methods to create/delete an EVS VNIC and
    plumb/unplumb ab IP interface and addresses on the EVS VNIC.
    """

    # TODO(gmoodalb): dnsmasq uses old style `ifreq', so 16 is the maximum
    # length including the NUL character. If we change it to use new style
    # `lifreq', then we will be able to extend the length to 32 characters.
    VNIC_NAME_MAXLEN = 15
    VNIC_NAME_PREFIX = 'dh'
    VNIC_NAME_SUFFIX = '_0'
    VNIC_NAME_LEN_WO_SUFFIX = VNIC_NAME_MAXLEN - \
        len(VNIC_NAME_SUFFIX)

    def __init__(self, conf):
        self.conf = conf
        # Since there is no connect_uri() yet, we need to do this ourselves
        # parse ssh://user@hostname
        suh = self.conf.evs_controller.split('://')
        if len(suh) != 2 or suh[0] != 'ssh' or not suh[1].strip():
            raise SystemExit(_("Specified evs_controller is invalid"))
        uh = suh[1].split('@')
        if len(uh) != 2 or not uh[0].strip() or not uh[1].strip():
            raise SystemExit(_("'user' and 'hostname' need to be specified "
                               "for evs_controller"))

        # save the user and EVS controller info
        self.uh = uh
        self._rad_connection = None
        # set the controller property for this host
        cmd = ['/usr/sbin/evsadm', 'show-prop', '-co', 'value', '-p',
               'controller']
        stdout = utils.execute(cmd)
        if conf.evs_controller != stdout.strip():
            cmd = ['/usr/sbin/evsadm', 'set-prop', '-p',
                   'controller=%s' % (conf.evs_controller)]
            utils.execute(cmd)

    @property
    def rad_connection(self):
        if (self._rad_connection is not None and
                self._rad_connection._closed is None):
            return self._rad_connection

        LOG.debug(_("Connecting to EVS Controller at %s as %s") %
                  (self.uh[1], self.uh[0]))

        self._rad_connection = radcon.connect_ssh(self.uh[1], user=self.uh[0])
        return self._rad_connection

    def fini_l3(self, device_name):
        ipif = net_lib.IPInterface(device_name)
        ipif.delete_ip()

    def init_l3(self, device_name, ip_cidrs, addrconf=False):
        """Set the L3 settings for the interface using data from the port.
           ip_cidrs: list of 'X.X.X.X/YY' strings
        """
        ipif = net_lib.IPInterface(device_name)
        for ip_cidr in ip_cidrs:
            ipif.create_address(ip_cidr)
        if addrconf:
            ipif.create_addrconf()

    # TODO(gmoodalb): - probably take PREFIX?? for L3
    def get_device_name(self, port):
        vnicname = (self.VNIC_NAME_PREFIX +
                    port.id)[:self.VNIC_NAME_LEN_WO_SUFFIX]
        vnicname += self.VNIC_NAME_SUFFIX
        return vnicname.replace('-', '_')

    def plug(self, tenant_id, network_id, port_id, datalink_name,
             namespace=None, prefix=None, protection=False):
        """Plug in the interface."""

        try:
            evsc = self.rad_connection.get_object(evsbind.EVSController())
            vports_info = evsc.getVPortInfo("vport=%s" % (port_id))
            if vports_info:
                vport_info = vports_info[0]
                # This is to handle HA when the 1st DHCP/L3 agent is down and
                # the second DHCP/L3 agent tries to connect its VNIC to EVS, we
                # will end up in "vport in use" error. So, we need to reset the
                # vport before we connect the VNIC to EVS.
                if vport_info.status == evsbind.VPortStatus.USED:
                    LOG.debug(_("Retrieving EVS: %s"), vport_info.evsuuid)
                    pat = radcli.ADRGlobPattern({'uuid': network_id,
                                                 'tenant': tenant_id})
                    evs_objs = self.rad_connection.list_objects(evsbind.EVS(),
                                                                pat)
                    if evs_objs:
                        evs = self.rad_connection.get_object(evs_objs[0])
                        evs.resetVPort(port_id, "force=yes")

                if not protection:
                    LOG.debug(_("Retrieving VPort: %s"), port_id)
                    pat = radcli.ADRGlobPattern({'uuid': port_id,
                                                 'tenant': tenant_id,
                                                 'evsuuid': network_id})
                    vport_objs = self.rad_connection.list_objects(
                        evsbind.VPort(), pat)
                    if vport_objs:
                        vport = self.rad_connection.get_object(vport_objs[0])
                        vport.setProperty("protection=none")
        except radcli.ObjectError as oe:
            raise EVSControllerError(oe.get_payload().errmsg)
        finally:
            self.rad_connection.close()

        dl = net_lib.Datalink(datalink_name)
        evs_vport = "%s/%s" % (network_id, port_id)
        dl.connect_vnic(evs_vport, tenant_id)

    def unplug(self, device_name, namespace=None, prefix=None):
        """Unplug the interface."""

        dl = net_lib.Datalink(device_name)
        dl.delete_vnic()
