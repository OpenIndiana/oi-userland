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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#

Puppet::Type.type(:pkg_mediator).provide(:pkg_mediator) do
    desc "Provider for Oracle Solaris mediators"
    confine :operatingsystem => [:solaris]
    defaultfor :osfamily => :solaris, :kernelrelease => ['5.11', '5.12']
    commands :pkg => '/usr/bin/pkg'
    mk_resource_methods

    def initialize(value={})
      super(value)
      @property_flush = { :set_args => [], :unset_args => [] }
    end

    def self.parse_mediator(line)
            name, _ver_src, version, _impl_src, impl, _impl_ver = line.split("\t")

            # Neither Implementation nor Version are required
            if impl.nil? || impl.empty?
                impl = :None
            end
            if version.nil? || version.empty?
                version = :None
            end

            return { :name => name,
                :ensure => :present,
                :implementation => impl,
                :version => version }
    end

    def self.get_mediator(name)
      return self.parse_mediator(pkg(:mediator, "-H", "-F", "tsv", name))
    end

    def self.instances
        pkg(:mediator, "-H", "-F", "tsv").split("\n").collect do |line|
            new(self.parse_mediator(line))
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
        if @property_hash[:ensure] == :present and not
          # Don't check values unless they are set in the manifest/resource
          (  @resource[:version].nil? && @resource[:implementation].nil? )
            # Both Version and Implementation must be expected or unspecified
            return ((version == @resource[:version]) ||
                     @resource[:version].nil? ) \
                   &&
                   ((implementation == @resource[:implementation] ||
                     @resource[:implementation].nil?))
        end
        @property_hash[:ensure] == :present
    end

    def build_flags
        if version == @resource[:version]
          # Current State is Correct, noop
        elsif @resource[:version] == :None && version != :None
          # version is set and should not be
          @property_flush[:unset_args] << '-V'
        elsif ! @resource[:version].nil?
          @property_flush[:set_args] << '-V' << @resource[:version]
        end

        if implementation == @resource[:implementation]
          # Current State is Correct, noop
        elsif @resource[:implementation] == :None && implementation != :None
          # implementation is set and should not be
            @property_flush[:unset_args] << '-I'
        elsif ! @resource[:implementation].nil?
            @property_flush[:set_args] << '-I' << @resource[:implementation]
        end

        # If there is no pre-existing resource there will be no properties
        # defined. If we got here and set_args is 0 we have unset_args
        # otherwise there would be no changes
        if @property_hash[:ensure].nil? && @property_flush[:set_args].size == 0
          raise Puppet::ResourceError.new(
            "Cannot unset absent mediator; use ensure => :absent instead of <property> => None")
        end
    end

    def flush
        pkg("set-mediator", @property_flush[:set_args], @resource[:name]) if
          @property_flush[:set_args].size > 0
        pkg("unset-mediator", @property_flush[:unset_args], @resource[:name]) if
          @property_flush[:unset_args].size > 0
        @property_hash = self.class.get_mediator(resource[:name])
    end

    # required puppet functions
    def create
        build_flags
    end

    def destroy
        # Absent mediators don't require any flag parsing, just remove them
        pkg("unset-mediator", @resource[:name])
    end
end
