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

Puppet::Type.type(:etherstub).provide(:etherstub) do
    desc "Provider for creating Solaris etherstubs"
    confine :operatingsystem => [:solaris]
    defaultfor :osfamily => :solaris, :kernelrelease => ['5.11', '5.12']
    commands :dladm => '/usr/sbin/dladm'

    def self.instances
        dladm("show-etherstub", "-p", "-o", "link").split(
              "\n").collect do |line|
            link = line.strip()
            new(:name => link, :ensure => :present)
        end
    end

    def add_options
        options = []
        if @resource[:temporary] == :true
            options << "-t"
        end
        options
    end

    def self.prefetch(resources)
        # pull the instances on the system
        etherstubs = instances

        # set the provider for the resource to set the property_hash
        resources.keys.each do |name|
            if provider = etherstubs.find{ |etherstub| etherstub.name == name}
                resources[name].provider = provider
            end
        end
    end

    def exists?
        @property_hash[:ensure] == :present
    end

    def create
        dladm("create-etherstub", add_options, @resource[:name])
    end

    def destroy
        dladm("delete-etherstub", add_options, @resource[:name])
    end
end
