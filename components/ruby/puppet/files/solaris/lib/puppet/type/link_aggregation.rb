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

require 'puppet/property/list'

Puppet::Type.newtype(:link_aggregation) do
    @doc = "Manage the configuration of Oracle Solaris link aggregations"

    ensurable

    newparam(:name) do
        desc "The name of the link aggregration"
        isnamevar
    end

    newparam(:temporary) do
        desc "Optional parameter that specifies that the aggreation is
              temporary.  Temporary aggregation links last until the next
              reboot."
        newvalues(:true, :false)
    end

    newproperty(:lower_links, :parent => Puppet::Property::List) do
        desc "Specifies an array of links over which the aggrestion is created."

        # ensure should remains an array
        def should
            @should
        end

        def insync?(is)
            is = [] if is == :absent or is.nil?
            is.sort == self.should.sort
        end

        # dladm returns multivalue entries delimited with a space
        def delimiter
            " "
        end

    end

    newproperty(:mode) do
        desc "Specifies which mode to set."
        newvalues(:trunk, :dlmp)
    end

    newproperty(:policy) do
        desc "Specifies the port selection policy to use for load spreading
              of outbound traffic."
    end

    newproperty(:lacpmode) do
        desc "Specifies whether LACP should be used and, if used, the mode
              in which it should operate"
        newvalues(:off, :active, :passive)
    end

    newproperty(:lacptimer) do
        desc "Specifies the LACP timer value"
        newvalues(:short, :long)
    end

    newproperty(:address) do
        desc "Specifies a fixed unicast hardware address to be used for the
              aggregation"
    end
end
