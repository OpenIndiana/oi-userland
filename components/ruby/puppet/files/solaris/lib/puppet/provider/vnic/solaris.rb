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

Puppet::Type.type(:vnic).provide(:vnic) do
    desc "Provider for creating VNICs in the Solaris OS"
    confine :operatingsystem => [:solaris]
    defaultfor :osfamily => :solaris, :kernelrelease => ['5.11', '5.12']
    commands :dladm => '/usr/sbin/dladm'

    def self.instances
        vnics = []
        dladm("show-vnic", "-p", "-o", "link,over,macaddress").split(
              "\n").collect do |line|
            link, over, mac = line.split(":", 3)
            next if not link =~ /^[[:alpha:]]([\w.]){1,29}([\d])$/i
            # remove the escape character
            vnics << new(:name => link,
                         :ensure => :present,
                         :lower_link => over,
                         :mac_address => mac.delete("\\"))
        end
        vnics
    end
        
    def self.prefetch(resources)
        # pull the instances on the system
        vnics = instances

        # set the provider for the resource to set the property_hash
        resources.keys.each do |name|
            if provider = vnics.find{ |vnic| vnic.name == name}
                resources[name].provider = provider
            end
        end
    end

    def lower_link
        @property_hash[:lower_link]
    end

    def lower_link=(value)
        dladm("modify-vnic", "-l", value, @resource[:name])
    end

    def mac_address
        @property_hash[:mac_address]
    end

    def mac_address=(value)
        dladm("modify-vnic", "-m", value, @resource[:name])
    end

    def add_options
       options = []
       if @resource[:temporary] == :true
         options << "-t"
       end

       if @resource[:mac_address]
           options << "-m" << @resource[:mac_address]
       end
       options
    end

    def exists?
        @property_hash[:ensure] == :present
    end

    def create
        dladm('create-vnic', '-l', @resource[:lower_link], add_options,
              @resource[:name])
    end

    def destroy
        dladm('delete-vnic', @resource[:name])
    end
end
