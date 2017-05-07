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
# Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved.
#

Puppet::Type.newtype(:svccfg) do
    @doc = "Manage SMF service properties with svccfg(1M)."

    ensurable do
        newvalue(:present) do
            provider.create
        end

        newvalue(:absent) do
            provider.destroy
        end

        newvalue(:delcust) do
            provider.delcust
        end
    end

    newparam(:name) do
        desc "The symbolic name for properties to manipulate.  This name is
              meaningful only within Puppet manifests and not expressed to
              SMF in any way."
        isnamevar
    end

    newparam(:fmri) do
        desc "SMF service FMRI to manipulate"
    end

    newparam(:property) do
        desc "Name of property - includes Property Group and Property.  If
              the service, instance, or property group does not exist, they
              will be created."
    end

    newparam(:type) do
        desc "Type of the property"
    end

    newparam(:value) do
        desc "Value of the property"
        munge do |value|
            # cast the value to an array.  This is done for the case where a
            # property needs to be set.  exists? will undo all of this and
            # revert the value into a simple string for comparisons.
            if not value.is_a? Array
                value = Array[value]
            end

            # wrap each entry in quotes
            value = value.collect{ |v| "\"#{v}\"" }

            value.insert(0, "(")
            value.insert(-1, ")")
        end
    end
end
