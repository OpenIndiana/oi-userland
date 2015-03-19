# vim: tabstop=4 shiftwidth=4 softtabstop=4

# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
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
import time

from cinder.brick import exception
from cinder.openstack.common.gettextutils import _
from cinder.openstack.common import log as logging
from cinder.openstack.common import processutils as putils

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

    def get_device_path(self, wwn):
        """Get the Device Name of the WWN"""
        try:
            out, err = self.execute('/usr/sbin/fcinfo', 'logical-unit', '-v')
        except putils.ProcessExecutionError as err:
            return None

        host_dev = None
        remote_port = None
        if out is not None:
            for line in [l.strip() for l in out.splitlines()]:
                if line.startswith("OS Device Name:"):
                    host_dev = line.split()[-1]
                if line.startswith("Remote Port WWN:"):
                    remote_port = line.split()[-1]
                if remote_port == wwn:
                    return host_dev

        return None

    def connect_volume(self, connection_properties, scan_tries):
        """Attach the volume to instance_name.

        connection_properties for Fibre Channel must include:
        target_portal - ip and optional port
        target_iqn - iSCSI Qualified Name
        target_lun - LUN id of the volume
        """
        device_info = {'type': 'block'}
        target_wwn = connection_properties['target_wwn']
        # Check for multiple target_wwn values in a list
        if isinstance(target_wwn, list):
            wwn = target_wwn[0]

        # The scsi_vhci disk node is not always present immediately.
        # Sometimes we need to reinitialize the connection to trigger
        # a refresh.
        for i in range(1, scan_tries):
            LOG.debug("Looking for Fibre Channel device")
            host_dev = self.get_device_path(wwn)

            if host_dev is not None and os.path.exists(host_dev):
                break
            else:
                self._refresh_connection()
                time.sleep(i ** 2)
        else:
            msg = _("Fibre Channel volume device not found.")
            LOG.error(msg)
            raise exception.NoFibreChannelVolumeDeviceFound()

        device_info['path'] = host_dev
        return device_info
