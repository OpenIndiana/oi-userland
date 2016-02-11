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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
#

require 'puppet/property/list'
Puppet::Type.newtype(:pkg_publisher) do
    @doc = "Manage Oracle Solaris package publishers"

    ensurable

    newparam(:name) do
        desc "The publisher name"
        isnamevar
    end

    newproperty(:origin, :parent => Puppet::Property::List) do
        desc "Which origin URI(s) to set.  For multiple origins, specify them
              as a list"

        # ensure should remains an array
        def should
            @should
        end

        def insync?(is)
            is = [] if is == :absent or is.nil?
            is.sort == self.should.sort
        end

        def retrieve
            provider.origin
        end

        # for origins with a file:// URI, strip any trailing / character
        munge do |value|
            if value.start_with? "file" and value.end_with? "/"
                value = value.chomp("/")
            else
                value
            end
        end
    end
    newproperty(:enable) do
        desc "Enable the publisher"
        newvalues(:true, :false)
    end

    newproperty(:sticky) do
        desc "Set the publisher 'sticky'"
        newvalues(:true, :false)
    end

    newproperty(:searchfirst) do
        desc "Set the publisher first in the search order"
        newvalues(:true)
    end

    newproperty(:searchafter) do
        desc "Set the publisher after the specified publisher in the search
              order"
    end

    newproperty(:searchbefore) do
        desc "Set the publisher before the specified publisher in the search
              order"
    end

    newproperty(:proxy) do
        desc "Use the specified web proxy URI to retrieve content for the
              specified origin or mirror"
    end

    newproperty(:sslkey) do
        desc "Specify the client SSL key"
    end

    newproperty(:sslcert) do
        desc "Specify the client SSL certificate"
    end

    newproperty(:mirror, :parent => Puppet::Property::List) do
        desc "Which mirror URI(s) to set.  For multiple mirrors, specify them
              as a list"
	
        # ensure should remains an array
        def should
            @should
        end

        def insync?(is)
            is = [] if is == :absent or is.nil?
            is.sort == self.should.sort
        end

        def retrieve
            provider.mirror
        end
        
        munge do |value|
            if value.start_with? "file" and value.end_with? "/"
                value = value.chomp("/")
            else
                value
            end
        end
    end
end
