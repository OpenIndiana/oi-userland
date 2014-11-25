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

require 'ipaddr'
require 'puppet/property/list'

# DNS options
simple_opts = ["debug", "rotate", "no-check-names", "inet6"]
arg_opts =  ["ndots", "timeout", "retrans", "attempts", "retry"]

Puppet::Type.newtype(:dns) do
    @doc = "Manage the configuration of the DNS client for Oracle Solaris"

    newparam(:name) do
        desc "The symbolic name for the DNS client settings to use.  This name
              is used for human reference only."
        isnamevar
    end

    newproperty(:nameserver, :parent => Puppet::Property::List) do
        desc "The IP address(es) the resolver is to query.  A maximum of
              3 IP addresses may be specified.  Specify multiple IP addresses
              as an array"

        # ensure should remains an array
        def should
            @should
        end

        def insync?(is)
            is = [] if is == :absent or is.nil?
            is.sort == self.should.sort
        end

        # svcprop returns multivalue entries delimited with a space
        def delimiter
            " "
        end

        validate do |value|
            begin
                ip = IPAddr.new(value)
            rescue ArgumentError
                raise Puppet::Error, "nameserver IP address:  #{value} is 
                    invalid"
            end
        end
    end

    newproperty(:domain) do
        desc "The local domain name"
    end

    newproperty(:search, :parent => Puppet::Property::List) do
        desc "The search list for host name lookup.  A maximum of 6 search
              entries may be specified.  Specify multiple search entries as an
              array."

        # ensure should remains an array
        def should
            @should
        end

        def insync?(is)
            is = [] if is == :absent or is.nil?
            is.sort == self.should.sort
        end

        # svcprop returns multivalue entries delimited with a space
        def delimiter
            " "
        end
    end

    newproperty(:sortlist, :parent => Puppet::Property::List) do
        desc "Addresses returned by gethostbyname() to be sorted.  Entries must
              be specified in IP 'slash notation'.  A maximum of 10 sortlist
              entries may be specified.  Specify multiple entries as an array."

        # ensure should remains an array
        def should
            @should
        end

        def insync?(is)
            is = [] if is == :absent or is.nil?
            is.sort == self.should.sort
        end

        # svcprop returns multivalue entries delimited with a space
        def delimiter
            " "
        end

        validate do |value|
            begin
                ip = IPAddr.new(value)
            rescue ArgumentError
                raise Puppet::Error, "sortlist IP address: #{value} is invalid"
            end
        end
    end

    newproperty(:options, :parent => Puppet::Property::List) do
        desc "Set internal resolver variables.  Valid values are debug,
              ndots:n, timeout:n, retrans:n, attempts:n, retry:n, rotate,
              no-check-names, inet6.  For values with 'n', specify 'n' as an
              integer.  Specify multiple options as an array."

        # ensure should remains an array
        def should
            @should
        end

        def insync?(is)
            is = [] if is == :absent or is.nil?
            is.sort == self.should.sort
        end

        # svcprop returns multivalue entries delimited with a space
        def delimiter
            " "
        end

        validate do |value|
            data = value.split(":")
            if data.length == 1
                raise Puppet::Error, "option #{value} is invalid" \
                    if not simple_opts.include? data[0]
            elsif data.length == 2
                raise Puppet::Error, "option #{value} is invalid" \
                    if not arg_opts.include? data[0]

                # attempt to cast the integer specified
                begin
                    check = Integer(data[1])
                rescue ArgumentError
                    raise Puppet::Error, "option #{value} is invalid"
                end 
            else
                raise Puppet::Error, "option #{value} is invalid"
            end
        end
    end
end
