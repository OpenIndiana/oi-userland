# vim: tabstop=4 shiftwidth=4 softtabstop=4
#
# Copyright (c) 2014, 2015, Oracle and/or its affiliates. All rights reserved.
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
"""
Solaris Driver and supporting meta-classes.
"""
from oslo_log import log as logging

from ironic.drivers import base
from ironic.drivers.modules import ipmitool
from ironic.drivers.modules import solaris_ipmitool

LOG = logging.getLogger(__name__)


class SolarisAndIPMIToolDriver(base.BaseDriver):
    """Solaris + IPMITool driver.

    This driver implements the 'core' functionality, combining
    :class:'ironic.drivers.ipmi.IPMI' for power on/off and reboot with
    :class:'ironic.drivers.solaris for image deployment. Implementations are in
    those respective classes; this class is merely the glue between them.
    """

    def __init__(self):
        LOG.debug(_("Loading Solaris And IPMI Tool Driver"))
        self.power = ipmitool.IPMIPower()
        self.deploy = solaris_ipmitool.SolarisDeploy()
        self.console = None   # Not implemented yet
        self.rescue = None    # Not implemented yet
        self.management = solaris_ipmitool.SolarisManagement()
        self.inspect = solaris_ipmitool.SolarisInspect()
        self.vendor = None    # No VendorSpecific methods yet
