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

Puppet::Type.type(:pkg_facet).provide(:pkg_facet) do
    desc "Provider for Oracle Solaris facets"
    confine :operatingsystem => [:solaris]
    defaultfor :osfamily => :solaris, :kernelrelease => ['5.11', '5.12']
    commands :pkg => '/usr/bin/pkg'

    def self.instances
        pkg(:facet, "-H", "-F", "tsv").split("\n").collect do |line|
            name, value = line.split
            new(:name => name,
                :ensure => :present,
                :value => value.downcase)
        end 
    end

    def self.prefetch(resources)
        # pull the instances on the system
        facets = instances

        # set the provider for the resource to set the property_hash
        resources.keys.each do |name|
            if provider = facets.find{ |facet| facet.name == name}
                resources[name].provider = provider
            end
        end
    end

    def value
        @property_hash[:value]
    end

    def exists?
        # only compare against @resource if one is provided via manifests
        if @property_hash[:ensure] == :present and @resource[:value] != nil
            # retrieve the string representation of @resource[:value] since it
            # gets translated to an object by Puppet
            return (@property_hash[:ensure] == :present and \
                    @property_hash[:value].downcase == \
                        @resource[:value].downcase)
        end
        @property_hash[:ensure] == :present
    end

    # required puppet functions
    def create
        pkg("change-facet", "#{@resource[:name]}=#{@resource[:value]}")
    end

    def destroy
        pkg("change-facet", "#{@resource[:name]}=None")
    end
end
