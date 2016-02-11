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

Puppet::Type.newtype(:evs_ipnet) do
    @doc = "Manage the configuration of IPnet (subnet of IPv4 or IPv6 
            addresses)"

    ensurable
    newparam(:name) do
        desc "The full name of IPnet including tenant name"
        validate do |value|
            if value.split("/").length != 3
                raise Puppet::Error, "Invalid IPnet name\n"\
                    "Name convention must be <tenant>/<evs>/<ipnet>"
            end
        end
    end
    
    ## read-only properties (updatable when idle) ##
    newproperty(:subnet) do
        desc "Subnet (either IPv4 or IPv6) for the IPnet"
    end
    
    newproperty(:defrouter) do
        desc "The IP address of the default router for the given IPnet"
    end

    newproperty(:uuid) do
        desc "UUID of the IPnet"
    end
    
    ## read/write property (settable upon creation) ##
    newproperty(:pool) do
        desc "Sub-ranges of IP addresses within a subnet"
    end
end
