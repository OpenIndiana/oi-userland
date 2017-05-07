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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#

Puppet::Type.newtype(:vnic) do
    @doc = "Manage the configuration of Oracle Solaris Virtual NICs (VNICs)"

    ensurable

    newparam(:name) do
        desc "The name of the VNIC"

        isnamevar

        validate do |vnic_value|
           if not vnic_value =~ /^[[:alpha:]]([\w.]){1,29}([\d])$/i
               raise Puppet::Error, "Invalid VNIC name: #{vnic_value}"
           end
        end
    end

    newparam(:temporary)  do
        desc "Optional parameter that specifies that  the  VNIC  is  temporary. 
              Temporary VNICs last until the next reboot."
        newvalues(:true, :false)
    end

    newproperty(:lower_link) do
        desc "The name of the physical datalink over which the VNIC is 
              operating"
        validate do |link_value|
            if not link_value =~ /^[[:alpha:]]([\w.]){1,29}([\d])$/i
                raise Puppet::Error, "Invalid lower-link: #{link_value}"
            end
        end
    end

    newproperty(:mac_address) do
        desc "Sets the VNIC's MAC address based on  the  specified value."
        validate do |mac_value|
            if not mac_value =~ /^([[:xdigit:]]{1,2}[:-]){5}[[:xdigit:]]{1,2}$/i
                raise Puppet::Error, "Invalid MAC address: #{mac_value}" 
            end
        end
    end
end
