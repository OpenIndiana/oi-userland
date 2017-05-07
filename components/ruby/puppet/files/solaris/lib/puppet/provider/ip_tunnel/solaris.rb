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

Puppet::Type.type(:ip_tunnel).provide(:ip_tunnel) do
    desc "Provider for managing Oracle Solaris IP Tunnel links"
    confine :operatingsystem => [:solaris]
    defaultfor :osfamily => :solaris, :kernelrelease => ['5.11', '5.12']
    commands :dladm => '/usr/sbin/dladm'

    def self.instances
        dladm("show-iptun", "-p", "-o", "link,type,local,remote").split(
              "\n").collect do |line|
            link, type, local, remote = line.split(":")
            new(:name => link,
                :ensure => :present,
                :tunnel_type => type,
                :local_address => local,
                :remote_address => remote)
        end
    end
        
    def self.prefetch(resources)
        # pull the instances on the system
        ip_tunnels = instances

        # set the provider for the resource to set the property_hash
        resources.keys.each do |name|
            if provider = ip_tunnels.find{ |ip_tunnel| ip_tunnel.name == name}
                resources[name].provider = provider
            end
        end
    end

    [:tunnel_type, :local_address, :remote_address].each do |field|
        define_method(field) do
            begin
                @property_hash[field]
            end
        end
    end

    def local_address=(value)
        dladm("modify-iptun", "-a", "local=#{value}", @resource[:name])
    end

    def remote_address=(value)
        dladm("modify-iptun", "-a", "remote=#{value}", @resource[:name])
    end

    def add_options
       options = []
       if @resource[:temporary] == :true
         options << "-t"
       end

       if tunnel_type = @resource[:tunnel_type] and tunnel_type != nil
           options << "-T" << resource[:tunnel_type]
       end

       if local = @resource[:local_address] and local != nil
           options << "-a" << "local=#{local}"
       end

       if remote = @resource[:remote_address] and remote != nil
           options << "-a" << "remote=#{remote}"
       end
       options
    end

    def exists?
        @property_hash[:ensure] == :present
    end

    def create
        dladm('create-iptun', add_options, @resource[:name])
    end

    def destroy
        dladm('delete-iptun', @resource[:name])
    end
end
