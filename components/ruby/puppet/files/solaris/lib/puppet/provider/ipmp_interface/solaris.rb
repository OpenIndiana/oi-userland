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

Puppet::Type.type(:ipmp_interface).provide(:ipmp_interface) do
    desc "Provider for management of IPMP interfaces for Oracle Solaris"
    confine :operatingsystem => [:solaris]
    defaultfor :osfamily => :solaris, :kernelrelease => ['5.11', '5.12']
    commands :ipadm => '/usr/sbin/ipadm'

    def self.instances
        ifaces = []
        ipadm("show-if", "-p", "-o", "IFNAME,CLASS,OVER").each_line do |line|
            name, linkclass, over = line.strip().split(":", 3)
            next if linkclass != "ipmp"
            ifaces << new(:name => name.strip(),
                          :ensure => :present,
                          :interfaces => over)
        end
        ifaces
    end
        
    def self.prefetch(resources)
        # pull the instances on the system
        ifaces = instances

        # set the provider for the resource to set the property_hash
        resources.keys.each do |name|
            if provider = ifaces.find{ |iface| iface.name == name}
                resources[name].provider = provider
            end
        end
    end

    def interfaces
        @property_hash[:interfaces]
    end

    def interfaces=(value)
        current = self.interfaces.split()

        remove_list = []
        for entry in current - value
            remove_list << "-i" << entry
        end

        add_list = []
        for entry in value - current
            add_list << "-i" << entry
        end

        if not add_list.empty?
            ipadm("add-ipmp", add_list, @resource[:name])
        end

        if not remove_list.empty?
            ipadm("remove-ipmp", remove_list, @resource[:name])
        end
    end

    def add_options
        options = []
        if @resource[:temporary] == :true
            options << "-t"
        end
        for iface in @resource[:interfaces] do
            options << "-i" << iface
        end
        options
    end

    def exists?
        @property_hash[:ensure] == :present
    end

    def create
        ipadm('create-ipmp', add_options, @resource[:name])
    end

    def destroy
        for iface in self.interfaces.each_line do
            ipadm("remove-ipmp", "-i", iface, @resource[:name])
        end
        ipadm('delete-ipmp', @resource[:name])
    end
end
