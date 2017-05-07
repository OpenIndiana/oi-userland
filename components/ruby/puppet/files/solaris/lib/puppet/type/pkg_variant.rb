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

Puppet::Type.newtype(:pkg_variant) do
    @doc = "Manage Oracle Solaris package variants"

    ensurable do
        # remove the ability to specify :absent as deletion of variants is not
        # supported.  New values must be set.
        newvalue(:present) do
            provider.create
        end
    end

    newparam(:name) do
        desc "The variant name"
        isnamevar
    end

    newproperty(:value) do
        desc "The value for the variant"
    end
end
