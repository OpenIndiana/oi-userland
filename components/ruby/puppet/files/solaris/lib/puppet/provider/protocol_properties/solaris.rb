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

Puppet::Type.type(:protocol_properties).provide(:protocol_properties) do
    desc "Provider for managing Oracle Solaris protocol object properties"
    confine :operatingsystem => [:solaris]
    defaultfor :osfamily => :solaris, :kernelrelease => ['5.11', '5.12']
    commands :ipadm => '/usr/sbin/ipadm'

    def initialize(value={})
        super(value)
        @protoprops = {}
    end

    def self.instances
        props = {}

        ipadm("show-prop", "-c", "-o", "PROTO,PROPERTY,CURRENT").split(
              "\n").collect do |line|
            protocol, property, value = line.strip().split(":")
            next if value == nil
            if not props.has_key? protocol
                props[protocol] = {}
            end
            props[protocol][property] = value
        end

        protocols = []
        props.each do |key, value|
            protocols << new(:name => key,
                             :ensure => :present,
                             :properties => value)
        end
        protocols
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
            ipadm("set-prop", "-p", "#{key}=#{value}", @resource[:name])
        end
    end

    def exists?
        if @resource[:properties] == nil
            return :false
        end

        @resource[:properties].each do |key, value|
            p = exec_cmd(command(:ipadm), "show-prop","-c", "-p", key,
                         "-o", "CURRENT", @resource[:protocol])
            if p[:exit] == 1
                Puppet.warning "Property '#{key}' not found for protocol " \
                               "#{@resource[:protocol]}"
                next
            end

            if p[:out].strip != value
                @protoprops[key] = value
            end
        end

        return @protoprops.empty?
    end

    def create
        @protoprops.each do |key, value|
            ipadm("set-prop", "-p", "#{key}=#{value}", @resource[:name])
        end
    end

    def exec_cmd(*cmd)
        output = Puppet::Util::Execution.execute(cmd, :failonfail => false)
        {:out => output, :exit => $CHILD_STATUS.exitstatus}
    end
end
