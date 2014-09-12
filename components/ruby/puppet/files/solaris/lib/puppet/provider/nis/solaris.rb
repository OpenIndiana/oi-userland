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

Puppet::Type.type(:nis).provide(:nis) do
    desc "Provider for management of NIS client for Oracle Solaris"
    confine :operatingsystem => [:solaris]
    defaultfor :osfamily => :solaris, :kernelrelease => ['5.11', '5.12']
    commands :svccfg => '/usr/sbin/svccfg', :svcprop => '/usr/bin/svcprop'

    class << self; attr_accessor :client_fmri, :domain_fmri end
    Client_fmri = "svc:/network/nis/client"
    Domain_fmri = "svc:/network/nis/domain"

    def initialize(value={})
        super(value)
        @client_refresh = false
        @domain_refresh = false
    end

    def self.instances
        props = {}
        validprops = Puppet::Type.type(:nis).validproperties

        [Client_fmri, Domain_fmri].each do |svc|
            svcprop("-p", "config", svc).split("\n").collect do |line|
                data = line.split()
                fullprop = data[0]
                type = data[1]
                if data.length > 2
                    value = data[2..-1].join(" ")
                else
                    value = nil
                end

                pg, prop = fullprop.split("/")
                props[prop] = value if validprops.include? prop.to_sym
            end
        end
        props[:name] = "current"
        return Array new(props)
    end

    # svc:/network/nis/client properties
    [:use_broadcast, :use_ypsetme].each do |field|
        define_method(field) do
            begin
                svcprop("-p", "config/" + field.to_s, Client_fmri).strip()
            rescue
                # if the property isn't set, don't raise an error
                nil
            end
        end

        define_method(field.to_s + "=") do |should|
            begin
                svccfg("-s", Client_fmri, "setprop", "config/" + field.to_s,
                       "=", '"' + should.to_s + '"')
            rescue => detail
                raise Puppet::Error,
                    "Unable to set #{field.to_s} to #{should.inspect}\n"
                    "#{detail}\n"
            end
            @client_refresh = true
        end
    end

    # svc:/network/nis/domain properties
    [:domainname, :ypservers, :securenets].each do |field|
        define_method(field) do
            begin
                svcprop("-p", "config/" + field.to_s, Domain_fmri).strip()
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

                    svccfg("-s", Domain_fmri, "setprop",
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
                    svccfg("-s", Domain_fmri, "setprop",
                           "config/" + field.to_s, "=", value)
                end
            rescue => detail
                raise Puppet::Error,
                    "Unable to set #{field.to_s} to #{should.inspect}\n"
                    "#{detail}\n"
            end
            @domain_refresh = true
        end
    end

    def flush
        if @domain_refresh == true
            svccfg("-s", Domain_fmri, "refresh")
        end
        if @client_refresh == true
            svccfg("-s", Client_fmri, "refresh")
        end
    end
end
