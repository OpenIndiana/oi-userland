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

Puppet::Type.newtype(:boot_environment) do
    @doc = "Manage Oracle Solaris Boot Environments (BEs)"

    ensurable

    newparam(:name) do
        desc "The BE name"
        validate do |value|
            raise Puppet::Error, "Invalid BE name:  #{value}" unless
                value =~ /^[\d\w\.\-\:\_]+$/
        end
        isnamevar
    end

    newparam(:description) do
        desc "Description for the new BE"
    end

    newparam(:clone_be) do
        desc "Create a new BE from an existing inactive BE"
    end

    newparam(:options) do
        desc "Create the datasets for a new BE with specific ZFS
              properties.  Specify options as a hash."
    end

    newparam(:zpool) do
        desc "Create the new BE in the specified zpool"
    end

    newproperty(:activate) do
        desc "Activate the specified BE"
        newvalues(:true, :false)
    end
end
