# vim: tabstop=4 shiftwidth=4 softtabstop=4

# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
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

"""Generic Solaris Fibre Channel utilities."""

import os
import platform
import time

from oslo_concurrency import processutils as putils
from oslo_log import log as logging

from os_brick import exception
import oslo_i18n

LOG = logging.getLogger(__name__)


class SolarisFibreChannel(object):
    def __init__(self, *args, **kwargs):
        self.execute = putils.execute

    def _get_fc_hbas(self):
        """Get Fibre Channel HBA information."""
        out = None
        try:
            out, err = self.execute('/usr/sbin/fcinfo', 'hba-port')
        except putils.ProcessExecutionError as err:
            return None

        if out is None:
            LOG.info(_("Cannot find any Fibre Channel HBAs"))
            return None

        hbas = []
        hba = {}
        for line in out.splitlines():
            line = line.strip()
            # Collect the following hba-port data:
            # 1: Port WWN
            # 2: State (online|offline)
            # 3: Node WWN
            if line.startswith("HBA Port WWN:"):
                # New HBA port entry
                hba = {}
                wwpn = line.split()[-1]
                hba['port_name'] = wwpn
                continue
            elif line.startswith("Port Mode:"):
                mode = line.split()[-1]
                # Skip Target mode ports
                if mode != 'Initiator':
                    break
            elif line.startswith("State:"):
                state = line.split()[-1]
                hba['port_state'] = state
                continue
            elif line.startswith("Node WWN:"):
                wwnn = line.split()[-1]
                hba['node_name'] = wwnn
                continue
            if len(hba) == 3:
                hbas.append(hba)
                hba = {}
        return hbas

    def get_fc_wwnns(self):
        """Get Fibre Channel WWNNs from the system, if any."""
        hbas = self._get_fc_hbas()
        if hbas is None:
            return None

        wwnns = []
        for hba in hbas:
            if hba['port_state'] == 'online':
                wwnn = hba['node_name']
                wwnns.append(wwnn)
        return wwnns

    def get_fc_wwpns(self):
        """Get Fibre Channel WWPNs from the system, if any."""
        hbas = self._get_fc_hbas()
        if hbas is None:
            return None

        wwpns = []
        for hba in hbas:
            if hba['port_state'] == 'online':
                wwpn = hba['port_name']
                wwpns.append(wwpn)
        return wwpns

    def _refresh_connection(self):
        """Force the link reinitialization to make the LUN present."""
        wwpns = self.get_fc_wwpns()
        for wwpn in wwpns:
            self.execute('/usr/sbin/fcadm', 'force-lip', wwpn)

    def _get_device_path(self, wwn, target_lun):
        """Get the Device path for the specified LUN.

        The output of CMD below is like this:

        OS Device Name: /dev/rdsk/c0t600C0FF0000000000036223AE73EB705d0s2
               HBA Port WWN: 210100e08b27a8a1
                       Remote Port WWN: 256000c0ffc03622
                               LUN: 0
                       Remote Port WWN: 216000c0ff803622
                               LUN: 0
               HBA Port WWN: 210000e08b07a8a1
                       Remote Port WWN: 256000c0ffc03622
                               LUN: 0
                       Remote Port WWN: 216000c0ff803622
                               LUN: 0
               Vendor: SUN
               Product: StorEdge 3510
               Device Type: Disk device
        ......
        """
        try:
            out, err = self.execute('/usr/sbin/fcinfo', 'logical-unit', '-v')
        except putils.ProcessExecutionError as err:
            return None

        host_device = None
        remote_port = None
        if out is not None:
            for line in [l.strip() for l in out.splitlines()]:
                if line.startswith("OS Device Name:"):
                    host_device = line.split()[-1]
                if line.startswith("Remote Port WWN:"):
                    remote_port = line.split()[-1]
                if line.startswith("LUN:"):
                    lun = line.split()[-1]
                    if remote_port.upper() == wwn and \
                       int(lun) == int(target_lun):
                        return host_device

        return None

    def connect_volume(self, connection_properties, scan_tries):
        """Attach the volume to instance_name.

        connection_properties for Fibre Channel must include:
        target_wwn - Specified port WWNs
        target_lun - LUN id of the volume
        """
        device_info = {'type': 'block'}
        target_wwn = connection_properties['target_wwn']
        target_lun = connection_properties['target_lun']
        wwns = []
        if isinstance(target_wwn, list):
            wwns = target_wwn
        else:
            wwns.append(target_wwn)

        # The scsi_vhci disk node is not always present immediately.
        # Sometimes we need to reinitialize the connection to trigger
        # a refresh.
        for i in range(1, scan_tries):
            # initiator needs time to refresh the LU list
            time.sleep(i * 2)
            host_device = self._get_device_path(wwns[0], target_lun)

            if host_device is not None and os.path.exists(host_device):
                break
            else:
                self._refresh_connection()
        else:
            msg = _("Fibre Channel volume device not found.")
            LOG.error(msg)
            raise exception.NoFibreChannelVolumeDeviceFound()

        # Set the label EFI to the disk on SPARC before it is accessed and
        # make sure the correct device path with slice 0
        # (like '/dev/rdsk/c0t600xxxd0s0').
        if platform.processor() == 'sparc':
            tmp_dev_name = host_device.rsplit('s', 1)
            disk_name = tmp_dev_name[0].split('/')[-1]
            (out, _err) = self.execute('/usr/sbin/format', '-L', 'efi', '-d',
                                       disk_name)
            host_device = '%ss0' % tmp_dev_name[0]

        device_info['path'] = host_device
        return device_info
