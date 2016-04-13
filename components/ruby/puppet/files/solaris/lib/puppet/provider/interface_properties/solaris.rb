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

Puppet::Type.type(:interface_properties).provide(:interface_properties) do
    desc "Provider for managing Oracle Solaris interface properties"
    confine :operatingsystem => [:solaris]
    defaultfor :osfamily => :solaris, :kernelrelease => ['5.11', '5.12']
    commands :ipadm => '/usr/sbin/ipadm'

    def initialize(value={})
        super(value)
        @ifprops = {}
    end

    def self.instances
        props = {}

        ipadm("show-ifprop", "-c", "-o",
              "IFNAME,PROPERTY,PROTO,CURRENT").split("\n").collect do |line|
            ifname, property, proto, value = line.strip().split(":")
            fullname = ifname + "/" + proto
            if not props.has_key? fullname
                props[fullname] = {}
            end
            props[fullname][property] = value
        end

        interfaces = []
        props.each do |key, value|
            interfaces << new(:name => key,
                              :ensure => :present,
                              :properties => value)
        end
        interfaces
    end

    def self.prefetch(resources)
        # pull the instances on the system
        props = instances

        # set the provider for the resource to set the property_hash
        resources.keys.each do |name|
            if provider = props.find{ |prop| prop.name == name}
                resources[name].provider = provider
            end
        end
    end

    def properties
        @property_hash[:properties]
    end

    def properties=(value)
        value.each do |key, value|
            ipadm("set-ifprop", "-p", "#{key}=#{value}", @resource[:name])
        end
    end

    def exists?
        if @resource[:properties] == nil
            return :false
        end

        ifname, protocol = @resource[:interface].split("/")

        @resource[:properties].each do |key, value|
            p = exec_cmd(command(:ipadm), "show-ifprop", "-m", protocol,
                         "-p", key, "-c", "-o", "CURRENT", ifname)

            if p[:exit] == 1
                Puppet.warning "Property '#{key}' not found for interface
                                #{ifname}"
                next
            end

            if p[:out].strip != value
                @ifprops[key] = value
            end
        end

        return @ifprops.empty?
    end

    def create
        name, proto = @resource[:interface].split("/")
        @ifprops.each do |key, value|
            ipadm("set-ifprop", "-m", proto, "-p", "#{key}=#{value}", name)
        end
    end

    def exec_cmd(*cmd)
        output = Puppet::Util::Execution.execute(cmd, :failonfail => false)
        {:out => output, :exit => $CHILD_STATUS.exitstatus}
    end
end
