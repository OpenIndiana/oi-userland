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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
#

Puppet::Type.type(:pkg_publisher).provide(:pkg_publisher) do
    desc "Provider for Solaris publishers"
    confine :operatingsystem => [:solaris]
    defaultfor :osfamily => :solaris, :kernelrelease => ['5.11', '5.12']
    commands :pkg => '/usr/bin/pkg'

    def self.instances
        publishers = {}
        publisher_order = []
        pkg(:publisher, "-H", "-F", "tsv").split("\n").collect do |line|
            name, sticky, syspub, enabled, type, status, origin, proxy = \
                line.split("\t")

            # set the order of the publishers
            if not publisher_order.include?("name")
                publisher_order << name
            end
            # strip off any trailing "/" characters
            if origin.end_with?("/")
                origin = origin[0..-2]
            end

            if publishers.has_key?(name)
                # if we've seen this publisher before, simply update the origin
                # array
	        if type.eql? "mirror"
                    publishers[name]["mirror"] << origin
		else
                    publishers[name]["origin"] << origin
		end

            else
                # create a new hash entry for this publisher
                publishers[name] = {'sticky' => sticky, 'enable' => enabled,
                                    'origin' => Array[],
				    'mirror' => Array[]}
					
		if type.eql? "mirror"
                    publishers[name]["mirror"] << origin
		else
                    publishers[name]["origin"] << origin
		end

                publishers[name]["proxy"] = proxy if proxy != "-"

                index = publisher_order.index(name)
                if index == 0
                    publishers[name]["searchfirst"] = true
                    publishers[name]["searchafter"] = nil
                else
                    publishers[name]["searchfirst"] = nil
                    publishers[name]["searchafter"] = publisher_order[index-1]
                end
            end
        end
        # create new entries for the system
        publishers.keys.collect do |publisher|
            new(:name => publisher,
                :ensure => :present,
                :sticky => publishers[publisher]["sticky"],
                :enable => publishers[publisher]["enable"],
                :origin => publishers[publisher]["origin"],
                :mirror => publishers[publisher]["mirror"],
                :proxy => publishers[publisher]["proxy"],
                :searchfirst => publishers[publisher]["searchfirst"],
                :searchafter => publishers[publisher]["searchafter"],
                :searchbefore => nil,
                :sslkey => nil,
                :sslcert => nil)
        end
    end

    def self.prefetch(resources)
        # pull the instances on the system
        publishers = instances

        # set the provider for the resource to set the property_hash
        resources.keys.each do |name|
            if provider = publishers.find{ |publisher| publisher.name == name}
                resources[name].provider = provider
            end
        end
    end

    # property getters - each getter does exactly the same thing so create
    # dynamic methods to handle them
    [:sticky, :enable, :origin, :mirror, :proxy, :searchfirst, :searchafter,
     :searchbefore, :sslkey, :sslcert].each do |property|
        define_method(property) do
            begin
                @property_hash[property]
            rescue
            end
        end
    end

    def exists?
        # only compare against @resource if one is provided via manifests
        if @property_hash[:ensure] == :present and @resource[:origin] != nil
            return @property_hash[:origin].sort() == @resource[:origin].sort()
        end
        @property_hash[:ensure] == :present
    end

    def build_origin
        origins = []
	
        # add all the origins from the manifest 
        if !@resource[:origin].nil?
	   for o in @resource[:origin] do
               origins << "-g" << o
           end
	end

        # add all the mirrors from the manifest 
	if !@resource[:mirror].nil?
	    for o in @resource[:mirror] do
                origins << "-m" << o
            end
	end
        # remove all the existing origins and mirrors
        if @property_hash != {}
           if !@property_hash[:origin].nil?
              for o in @property_hash[:origin] do
                  origins << "-G" << o
              end
	   end
           if !@property_hash[:mirror].nil?
              for o in @property_hash[:mirror] do
                  origins << "-M" << o
              end
           end
        end
        origins
    end

    def build_flags
        flags = []

        if searchfirst = @resource[:searchfirst] and searchfirst != ""
            if searchfirst == :true
                flags << "--search-first"
            end
        end

        if sticky = @resource[:sticky] and sticky != nil
            if sticky == :true
                flags << "--sticky"
            elsif sticky == :false
                flags << "--non-sticky"
            end
        end

        if searchafter = @resource[:searchafter] and searchafter != ""
            if pkg(:publisher, "-H", "-F", "tsv").split("\n").detect \
                { |line| line.split()[0] == searchafter }
                    flags << "--search-after" << searchafter
            else
                Puppet.warning "Publisher #{searchafter} not found.  " \
                               "Skipping --search-after argument"
            end
        end

        if searchbefore = @resource[:searchbefore] and searchbefore != ""
            if pkg(:publisher, "-H", "-F", "tsv").split("\n").detect \
                { |line| line.split()[0] == searchbefore }
                    flags << "--search-before" << searchbefore
            else
                Puppet.warning "Publisher #{searchbefore} not found.  " \
                               "Skipping --search-before argument"
            end
        end

        if proxy = @resource[:proxy]
            flags << "--proxy" << proxy
        end

        if sslkey = @resource[:sslkey]
            flags << "-k" << sslkey
        end

        if sslcert = @resource[:sslcert]
            flags << "-c" << sslcert
        end
        flags
    end

    # property setters
    def sticky=(value)
        if value == :true
            pkg("set-publisher", "--sticky", @resource[:name])
        else
            pkg("set-publisher", "--non-sticky", @resource[:name])
        end
    end

    def enable=(value)
        if value == :true
            pkg("set-publisher", "--enable", @resource[:name])
        else
            pkg("set-publisher", "--disable", @resource[:name])
        end
    end

    def searchfirst=(value)
        if value == :true
            pkg("set-publisher", "--search-first", @resource[:name])
        end
    end

    def searchbefore=(value)
        pkg("set-publisher", "--search-before", value, @resource[:name])
    end

    def searchafter=(value)
        pkg("set-publisher", "--search-after", value, @resource[:name])
    end

    def proxy=(value)
        pkg("set-publisher", "--proxy", value, @resource[:name])
    end

    def sslkey=(value)
        pkg("set-publisher", "-k", value, @resource[:name])
    end

    def sslcert=(value)
        pkg("set-publisher", "-c", value, @resource[:name])
    end

    # required puppet functions
    def create
        pkg("set-publisher", build_flags, build_origin, @resource[:name])
        # pkg(5) does not allow for a new publisher to be set with the disabled
        # flag, so check for it after setting the publisher
        if enable = @resource[:enable] and enable != nil
            if enable == :false
                pkg("set-publisher", "--disable", @resource[:name])
            end
        end
    end
    
    def mirror=(value)
        create
    end

    def destroy
        pkg("unset-publisher", @resource[:name])
    end
end
