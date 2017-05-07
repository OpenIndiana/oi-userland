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
device package data
"""
class ddu_package_object(object):
    """
    device package data
    """
    def __init__(self, pkg_type, pkg_name, pkg_location, inf_link = "",
                 compatible_name = "", flags_64bit = "",
                 device_descriptor = "", third_party_from_search = False):
        self.pkg_type = pkg_type
        self.pkg_name = pkg_name
        self.pkg_location = pkg_location
        self.inf_link = inf_link
        self.compatible_name = compatible_name
        self.flags_64bit = flags_64bit
        self.device_descriptor = device_descriptor
        self.third_party_from_search = third_party_from_search

    def get_pkg_type(self):
        return self.pkg_type

    def get_pkg_name(self):
        return self.pkg_name

    def get_pkg_location(self):
        return self.pkg_location

    def get_inf_link(self):
        return self.inf_link

    def get_compatible_name(self):
        return self.compatible_name

    def get_flags_64bit(self):
        return self.flags_64bit

    def get_device_descriptor(self):
        return self.device_descriptor

    def get_third_party_from_search(self):
        return self.third_party_from_search
