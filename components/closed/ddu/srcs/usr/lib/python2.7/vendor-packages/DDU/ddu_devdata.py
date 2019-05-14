#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
#
# Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.
#
"""
device data
"""
import commands

ABSPATH = '/usr/ddu'
class ddu_dev_data(object):
    """
    device data
    """
    def __init__(self, item_id, parent_item_id, description, device_id,
                 class_code, pci_path, driver_name, instance_id,
                 attach_status, vendor_id, device_type
                ):


        '''
        Constructor
        '''
        self.item_id = item_id
        self.parent_item_id = parent_item_id
        self.description = description
        self.device_id = device_id
        self.class_code = class_code
        self.pci_path = pci_path
        self.driver_name = driver_name
        self.instance_id = instance_id
        self.attach_status = attach_status
        self.vendor_id = vendor_id
        self.device_type = device_type


    def get_compatible_name_string(self):
        """get device compatible string"""
        status, output = commands.getstatusoutput(
                                  '%s/scripts/det_info.sh %s CLASS=%s' %
                                  (ABSPATH, str(self.pci_path),
                                  str(self.class_code)))
        status, output_find = commands.getstatusoutput(
                                       "/usr/bin/grep \"compatible name:\" %s"
                                       % output)
        del status
        compatible_string = output_find.split(":")[1]. \
                            replace("(", " ").replace(")", " "). \
                            replace("  "," ").strip()
        return compatible_string

    def get_binding_name_string(self):
        """get device binding name string"""
        status, output = commands.getstatusoutput(
                                  '%s/scripts/det_info.sh %s CLASS=%s' %
                                  (ABSPATH, str(self.pci_path),
                                  str(self.class_code)))
        status, output_find = commands.getstatusoutput(
                                       "/usr/bin/grep \"binding name:\" %s"
                                       % output)
        del status
        binding_string = output_find.split(":")[1]. \
                            replace("  "," ").strip()
        return binding_string

    def get_item_id(self):
        return self.item_id

    def get_parent_item_id(self):
        return self.parent_item_id

    def get_description(self):
        return self.description

    def get_device_id(self):
        return self.device_id

    def get_class_code(self):
        return self.class_code

    def get_pci_path(self):
        return self.pci_path

    def get_driver_name(self):
        return self.driver_name

    def get_instance_id(self):
        return self.instance_id

    def get_attach_status(self):
        return self.attach_status

    def get_vendor_id(self):
        return self.vendor_id

    def get_device_type(self):
        return self.device_type
