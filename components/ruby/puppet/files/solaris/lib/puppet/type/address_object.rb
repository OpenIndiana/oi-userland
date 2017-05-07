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

Puppet::Type.newtype(:address_object) do
    @doc = "Manage the configuration of Oracle Solaris address objects"

    ensurable

    newparam(:name) do
        desc "The name of the address object or interface"
        isnamevar
    end

    newparam(:temporary) do
        desc "Optional parameter that specifies that the address object is
              temporary.  Temporary address objects last until the next reboot."
        newvalues(:true, :false)
    end

    newproperty(:address_type) do
        desc "The type of address object to create.  Valid values are static,
              dhcp, addrconf."
        # add from_gz as a valid value, even though users should not specify it
        newvalues(:static, :dhcp, :addrconf, :from_gz)
    end

    newproperty(:enable) do
        desc "Specifies the address object should be enabled or disabled.
              This property is only applied temporarily, until next reboot."
        newvalues(:true, :false)
    end

    newproperty(:address) do
        desc "A literal IP address or a hostname corresponding to the local
              end-point.  An optional prefix length may be specified.  Only
              valid with an address_type of 'static'"
    end

    newproperty(:remote_address) do
        desc "A literal IP address or a hostname corresponding to an optional
              remote end-point.  An optional prefix length may be specified.
              Only valid with an address_type of 'static'"
    end

    newproperty(:down) do
        desc "Specifies that the configured address should be marked down.
              Only valid with an address_type of 'static'."
        newvalues(:true, :false)
    end

    newproperty(:seconds) do
        desc "Specifies the amount of time in seconds to wait until the
              operation completes.  Only valid with an address_type of
              'dhcp'.  Valid values are a numerical value in seconds or
              'forever'"
    end

    newproperty(:hostname) do
        desc "Specifies the hostname to which the client would like the DHCP
              server to map the client's leased IPv4 address.  Only valid
              with an address_type of 'dhcp'"
    end

    newproperty(:interface_id) do
        desc "Specifies the local interface ID to be used for generating
              auto-configured addresses.  Only valid with an address_type of
              'addrconf'"
    end

    newproperty(:remote_interface_id) do
        desc "Specifies an optional remote interface ID to be used for
              generating auto-configured addresses.  Only valid with an
              address_type of 'addrconf'"
    end

    newproperty(:stateful) do
        desc "Specifies if stateful auto-configuration should be enabled or
              not."
        newvalues(:yes, :no)
    end

    newproperty(:stateless) do
        desc "Specifies if stateless auto-configuration should be enabled or
              not."
        newvalues(:yes, :no)
    end
end
