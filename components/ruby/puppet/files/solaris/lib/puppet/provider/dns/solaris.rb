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

Puppet::Type.type(:dns).provide(:dns) do
    desc "Provider for management of DNS for Oracle Solaris"
    confine :operatingsystem => [:solaris]
    defaultfor :osfamily => :solaris, :kernelrelease => ['5.11', '5.12']
    commands :svccfg => '/usr/sbin/svccfg', :svcprop => '/usr/bin/svcprop'

    Dns_fmri = "svc:/network/dns/client"

    def self.instances
        props = {}
        svcprop("-p", "config", Dns_fmri).split("\n").each do |line|
            fullprop, type, value = line.split(" ", 2)
            pg, prop = fullprop.split("/")
            props[prop] = value \
                if Puppet::Type.type(:dns).validproperties.include? prop
        end

        props[:name] = "current"
        return Array new(props)
    end

    Puppet::Type.type(:dns).validproperties.each do |field|
        define_method(field) do
            begin
                svcprop("-p", "config/" + field.to_s, Dns_fmri).strip()
            rescue
                # if the property isn't set, don't raise an error
                nil
            end
        end

        define_method(field.to_s + "=") do |should|
            begin
                if should.is_a? Array
                    # the first entry needs the open paren and the last entry
                    # needs the close paren
                    should[0] = "(" + should[0]
                    should[-1] = should[-1] + ")"

                    svccfg("-s", Dns_fmri, "setprop",
                           "config/" + field.to_s, "=", should)
                else
                    # Puppet seems to get confused about when to pass an empty
                    # string or "\"\"".  Catch either condition to handle
                    # passing values to SMF correctly
                    if should.to_s.empty? or should.to_s == '""'
                        value = should.to_s
                    else
                        value = "\"" + should.to_s + "\""
                    end
                    svccfg("-s", Dns_fmri, "setprop",
                           "config/" + field.to_s, "=", value)
                end
            rescue => detail
                raise Puppet::Error,
                    "Unable to set #{field.to_s} to #{should.inspect}\n"
                    "#{detail}\n"
            end
        end
    end

    def flush
        svccfg("-s", Dns_fmri, "refresh")
    end
end
