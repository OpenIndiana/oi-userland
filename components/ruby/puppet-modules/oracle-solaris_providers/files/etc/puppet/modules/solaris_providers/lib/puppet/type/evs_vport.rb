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

Puppet::Type.newtype(:evs_vport) do
    @doc = "Manage the configuration of EVS VPort"

    ensurable do
        newvalue(:present) do
            provider.create
        end
        
        newvalue(:absent) do
            provider.destroy
        end
        
        # Resets the specified VPort
        newvalue(:reset) do
            provider.reset
        end
    end

    newparam(:name) do
        desc "The full name of Virtual Port for EVS"
        munge do |value|
            if value.split("/").length != 3
                raise Puppet::Error, "Invalid VPort name\n" \
                    "Name convention must be <tenant>/<evs>/<vport>"
            else
                value
            end
        end
    end

    ## read/write properties (always updatable) ##
    newproperty(:cos) do
        desc "802.1p priority on outbound packets on the virtual port"
    end

    newproperty(:maxbw) do
        desc "The full duplex bandwidth for the virtual port"
    end

    newproperty(:priority) do
        desc "Relative priority of virtual port"
        newvalues("high", "medium", "low", "")
    end

    newproperty(:protection) do
        desc "Enables one or more types of link protection"
        # verify protection value: comma(,) separable
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

    ## read-only properties (Settable upon creation) ##
    newproperty(:ipaddr) do
        desc "The IP address associated with the virtual port"
    end

    newproperty(:macaddr) do
        desc "The MAC address associated with the virtual port"
    end

    newproperty(:uuid) do
        desc "UUID of the virtual port"
    end
end
