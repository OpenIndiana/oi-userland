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

require 'puppet/property/list'

Puppet::Type.newtype(:ipmp_interface) do
    @doc = "Manage the configuration of Oracle Solaris IPMP interfaces"

    ensurable

    newparam(:name) do
        desc "The name of the IP interface"
        isnamevar
    end

    newparam(:temporary)  do
        desc "Optional parameter that specifies that the IP interface is
              temporary.  Temporary interfaces last until the next reboot."
        newvalues(:true, :false)
    end

    newproperty(:interfaces, :parent => Puppet::Property::List) do
        desc "An array of interface names to use for the IPMP interface"

        # ensure should remains an array
        def should
            @should
        end

        def insync?(is)
            is = [] if is == :absent or is.nil?
            is.sort == self.should.sort
        end

        # ipadm returns multivalue entries delimited with a space
        def delimiter
            " "
        end

        validate do |name|
            cmd = Array["/usr/sbin/ipadm", "show-if", "-p", "-o", "IFNAME"]
            output = Puppet::Util::Execution.execute(cmd).split("\n")
            if name.class == Array
                check = output - name
                raise Puppet::Error, "Invalid interface(s) specified:  "
                    "#{check.inspect}" if not check.empty?
            else
                raise Puppet::Error, "Invalid interface specified: #{name}" \
                    if not output.include?(name)
            end
        end
    end
end
