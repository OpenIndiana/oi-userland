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

require 'ipaddr'
require 'puppet/property/list'

def valid_hostname?(hostname)
    return false if hostname.length > 255 or hostname.scan('..').any?
    hostname = hostname[0...-1] if hostname.index('.', -1)
    return hostname.split('.').collect { |i|
        i.size <= 63 and 
        not (i.rindex('-', 0) or i.index('-', -1) or i.scan(/[^a-z\d-]/i).any?)
    }.all?
end

Puppet::Type.newtype(:nis) do
    @doc = "Manage the configuration of the NIS client for Oracle Solaris"

    newparam(:domainname) do
        desc "The NIS domainname"
        isnamevar
    end

    newproperty(:ypservers, :parent => Puppet::Property::List) do
        desc "The hosts or IP addresses to use as NIS servers.  Specify
              multiple entries as an array"

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
                # the value wasn't a valid IP address, so check the hostname
                raise Puppet::Error, "ypserver entry:  #{value} is 
                    invalid" if not valid_hostname? value
            end
        end
    end

    newproperty(:securenets, :parent => Puppet::Property::List) do
        desc "Entries for /var/yp/securenets.  Each entry must be a 2 element
              array.  The first element must be either a host or a netmask.
              The second element must be an IP network address.  Specify
              multiple entires as an array of arrays"

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
            netmask, network = value
            # check the netmask
            begin
                ip = IPAddr.new(netmask)
            rescue ArgumentError
                # the value wasn't a valid IP address, so check the hostname
                raise Puppet::Error, "securenets entry:  #{value} has an
                    invalid netmask" if not valid_hostname? netmask
            end

            begin
                ip = IPAddr.net(network)
            rescue ArgumentError
                # the value wasn't a valid IP address
                raise Puppet::Error, "securenets entry:  #{value} has an 
                    invalid network"
            end
        end
    end

    newproperty(:use_broadcast) do
        desc "Send a broadcast datagram requesting needed bind information for
              a specific NIS server.  Valid vales are true, false"
        newvalues(:true, :false)
    end

    newproperty(:use_ypsetme) do
        desc "Only allow root on the client to change the binding to a desired
              server.  Valid values are true, false"
        newvalues(:true, :false)
    end
end
