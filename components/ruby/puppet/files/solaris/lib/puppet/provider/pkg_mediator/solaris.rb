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

Puppet::Type.type(:pkg_mediator).provide(:pkg_mediator) do
    desc "Provider for Oracle Solaris mediators"
    confine :operatingsystem => [:solaris]
    defaultfor :osfamily => :solaris, :kernelrelease => ['5.11', '5.12']
    commands :pkg => '/usr/bin/pkg'

    def self.instances
        pkg(:mediator, "-H", "-F", "tsv").split("\n").collect do |line|
            name, ver_src, version, impl_src, impl, impl_ver = line.split("\t")
            
            # Because implementation is an optional parameter, it may not be set.
            # If the implementation is not set, that needs to be captured in 
            # the output.
            if not impl
                impl = 'None'
            end

            new(:name => name,
                :ensure => :present,
                :implementation => impl,
                :version => version)
        end 
    end

    def self.prefetch(resources)
        # pull the instances on the system
        mediators = instances

        # set the provider for the resource to set the property_hash
        resources.keys.each do |name|
            if provider = mediators.find{ |mediator| mediator.name == name}
                resources[name].provider = provider
            end
        end
    end

    def exists?
        # only compare against @resource if one is provided via manifests
        if @property_hash[:ensure] == :present and @resource[:version] != nil
            return (@property_hash[:ensure] == :present and \
                   @property_hash[:version] == @resource[:version])
        end
        @property_hash[:ensure] == :present
    end

    def version
        @property_hash[:version]
    end

    def implementation
        @property_hash[:implementation]
    end

    def build_flags
        flags = []
        if version = @resource[:version] and version != nil
            flags << "-V" << @resource[:version]
        end

        if implementation = @resource[:implementation] and implementation != nil
            flags << "-I" << @resource[:implementation]
        end
        flags
    end

    # required puppet functions
    def create
        pkg("set-mediator", build_flags, @resource[:name])
    end

    def destroy
        pkg("unset-mediator", build_flags, @resource[:name])
    end
end
