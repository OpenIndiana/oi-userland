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

Puppet::Type.type(:link_aggregation).provide(:link_aggregation) do
    desc "Provider for creating Oracle Solaris link aggregations"
    confine :operatingsystem => [:solaris]
    defaultfor :osfamily => :solaris, :kernelrelease => ['5.11', '5.12']
    commands :dladm => '/usr/sbin/dladm'

    def self.instances
        dladm("show-aggr", "-p", "-o",
              "link,mode,policy,addrpolicy,lacpactivity,lacptimer").split(
              "\n").collect do |line|
            link, mode, policy, addrpolicy, lacpactivity, lacptimer = \
                line.split(":")

            links = []
            dladm("show-aggr", "-x", "-p", "-o", "port", link).split(
                  "\n").each do |portline|
                next if portline.strip() == ""
                links << portline.strip()
            end

            new(:name => link,
                :ensure => :present,
                :lower_links => links.join(" "),
                :mode => mode,
                :policy => policy,
                :address => addrpolicy,
                :lacpmode => lacpactivity,
                :lacptimer => lacptimer)
        end
    end

    def self.prefetch(resources)
        # pull the instances on the system
        aggrs = instances

        # set the provider for the resource to set the property_hash
        resources.keys.each do |name|
            if provider = aggrs.find{ |aggr| aggr.name == name}
                resources[name].provider = provider
            end
        end
    end

    # property getters
    [:lower_links, :mode, :policy, :lacpmode, :lacptimer,
     :address].each do |field|
        define_method(field) do
            @property_hash[field]
        end
    end

    # property setters
    def lower_links=(value)
        is_temporary?(@resource[:name])
        current = self.lower_links.split()
        remove_list = []
        for entry in current - value
            remove_list << "-l" << entry
        end

        add_list = []
        for entry in value - current
            add_list << "-l" << entry
        end

        if not add_list.empty?
            dladm("add-aggr", add_list, @resource[:name])
        end

        if not remove_list.empty?
            dladm("remove-aggr", remove_list, @resource[:name])
        end
    end

    def mode=(value)
        is_temporary?(@resource[:name])
        dladm("modify-aggr", "-m", value, @resource[:name])
    end

    def policy=(value)
        is_temporary?(@resource[:name])
        dladm("modify-aggr", "-P", value, @resource[:name])
    end

    def lacpmode=(value)
        is_temporary?(@resource[:name])
        dladm("modify-aggr", "-L", value, @resource[:name])
    end

    def lacptimer=(value)
        is_temporary?(@resource[:name])
        dladm("modify-aggr", "-T", value, @resource[:name])
    end

    def address=(value)
        is_temporary?(@resource[:name])
        dladm("modify-aggr", "-u", value, @resource[:name])
    end

    def add_options
        options = []
        if @resource[:temporary] == :true
            options << "-t"
        end

        if lowerlinks = @resource[:lower_links]
            if lowerlinks.is_a? Array
                for link in lowerlinks
                    options << "-l" << link
                end
            else
                options << "-l" << lowerlinks
            end
        end

        if mode = @resource[:mode]
            options << "-m" << mode
        end

        if policy = @resource[:policy]
            options << "-P" << policy
        end

        if lacpmode = @resource[:lacpmode]
            options << "-L" << lacpmode
        end

        if lacptimer = @resource[:lacptimer]
            options << "-T" << lacptimer
        end

        if address = @resource[:address]
            options << "-u" << address
        end
        options
    end

    def exists?
        @property_hash[:ensure] == :present
    end

    def create
        dladm("create-aggr", add_options, @resource[:name])
    end

    def destroy
        dladm("delete-aggr", add_options, @resource[:name])
    end

    def is_temporary?(name)
        p = exec_cmd(command(:dladm), "show-aggr", "-P", name)
        raise Puppet::Error, "Unable to change attributes of temporary " \
            "aggregation #{@resource[:name]}" if p[:exit] == 1
    end

    def exec_cmd(*cmd)
        output = Puppet::Util::Execution.execute(cmd, :failonfail => false)
        {:out => output, :exit => $CHILD_STATUS.exitstatus}
    end
end

