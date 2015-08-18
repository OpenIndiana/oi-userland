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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

Puppet::Type.newtype(:evs) do
    @doc = "Manage the configuration of Oracle Solaris Elastic Virtual Switch
           (EVS)"

    ensurable
    newparam(:name) do
        desc "The full name for EVS (including the tenant name)"
        validate do |value|
            if value.split("/").length != 2
                raise Puppet::Error, "Invalid EVS name\n"\
                    "Name convention must be <tenant>/<evs>"
            end
        end
    end

    ## read/write properties (always updatable) ##
    newproperty(:maxbw) do
        desc "The full duplex bandwidth for the virtual port"
    end

    newproperty(:priority) do
        desc "The relative priority for the virtual port"
        newvalues("high", "medium", "low", "")
    end

    newproperty(:protection) do
        desc "Enables one or more types of link protection"
        # verify protection value: comma(,) separatable
        validate do |value| 
            value.split(",").collect do |each_val|
                if not ["mac-nospoof", "restricted", "ip-nospoof", 
                    "dhcp-nospoof", "none", ""].include? each_val
                    raise Puppet::Error, "Invalid value \"#{each_val}\". "\
                        "Valid values are mac-nospoof, restricted, "\
                        "ip-nospoof, dhcp-nospoof, none."
                end
            end
        end
    end

    ## read-only properties (settable upon creation) ##
    newproperty(:l2_type) do
        desc "Define how an EVS will be implemented across machines"
        newvalues("vlan", "vxlan", "flat", "")
    end
    
    newproperty(:vlanid) do
        desc "VXLAN segment ID used to implement the EVS"
    end
    
    newproperty(:vni) do
        desc "VLAN ID used to implement the EVS"
    end

    newproperty(:uuid) do
        desc "UUID of the EVS instance"
    end
end
