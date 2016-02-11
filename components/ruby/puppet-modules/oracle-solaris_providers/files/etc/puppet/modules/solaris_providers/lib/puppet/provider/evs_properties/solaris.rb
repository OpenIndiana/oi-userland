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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#


Puppet::Type.type(:evs_properties).provide(:evs_properties) do
    desc "Provider for managing Oracle Solaris EVS properties"
    confine :operatingsystem => [:solaris]
    defaultfor :osfamily => :solaris, :kernelrelease => ["5.11", "5.12"]
    commands :evsadm => "/usr/sbin/evsadm"

    mk_resource_methods

    def initialize(value={})
        super(value)
        @property_flush = {}
    end

    def self.get_client_property
        client_property = {}
        begin
            p = evsadm("show-prop", "-c", "-o", "property,value")
        rescue Puppet::ExecutionFailure => e
            raise Puppet::Error, "Failed to prefetch client property: \n" \
                "#{e.inspect}"
        end

        property, value = p.strip.split(":", 2)
        value.gsub! "\\:", ":" 
        client_property[:name] = "client_property"
        client_property[:controller] = value
        
        Puppet.debug "Client Property: #{client_property.inspect}"
        client_property

    end

    def self.get_control_properties
        control_props = {}
        uplink_ports = []
        uri_templates = []
        vxlan_addrs = []
        begin
            evsadm("show-controlprop", "-c", "-o", 
                "property,value,vlan_range,vxlan_range,host,flat").\
                split("\n").collect do |each_prop|
                each_prop.gsub! "\\:", "\\"
                property, value, vlan_range, vxlan_range, host, flat = \
                    each_prop.strip().split(":")
                case property
                when "l2-type"
                    control_props[:l2_type] = value
                when "uplink-port"
                    next if value.empty?
                    host = "" if host == nil
                    val = "#{value};#{vlan_range};#{vxlan_range};#{host};"\
                        "#{flat}"
                    uplink_ports << val
                when "uri-template"
                    value.gsub! "\\", ":"
                    host = "" if host == nil
                    val = "#{value};#{host}"
                    uri_templates << val
                when "vlan-range"
                    control_props[:vlan_range] = value
                when "vxlan-addr"
                    host = "" if host == nil
                    val = "#{value};#{vxlan_range};#{host}"
                    vxlan_addrs << val
                when "vxlan-ipvers"
                    control_props[:vxlan_ipvers] = value
                when "vxlan-mgroup"
                    control_props[:vxlan_mgroup] = value
                when "vxlan-range"
                    control_props[:vxlan_range] = value
                end
            end
        rescue Puppet::ExecutionFailure => e
            # EVS controller is not set or invalid
            # Handle the exception at upper level
            raise
        end
        control_props[:name] = "controller_property"
        control_props[:uplink_port] = uplink_ports
        control_props[:uri_template] = uri_templates
        control_props[:vxlan_addr] = vxlan_addrs
        Puppet.debug "Control Properties: #{control_props.inspect}"
        control_props
    end

    def self.instances
        prop_instance = []
        client_property = get_client_property
        prop_instance << new(client_property)
        
        begin
            controller_property = get_control_properties
        rescue Puppet::ExecutionFailure => e
            # EVS controller is not set or invalid
            prop_instance << new({:name => "controller_property"})
        else
            # controller_property values are fetched
            prop_instance << new(controller_property)
        end
        prop_instance
    end

    def self.prefetch(resources)
        instances.each do |inst|
            if resource = resources[inst.name]
                resource.provider = inst
            end
        end
    end
    
    ### Define Setters ###
    ## Controller side property setup ##
    
    def l2_type=(value)
        @property_flush[:l2_type] = value
    end
    
    def uplink_port=(value)
        @property_flush[:uplink_port] = value
    end
    
    def uri_template=(value)
        @property_flush[:uri_template] = value
    end

    def vlan_range=(value)
        @property_flush[:vlan_range] = value
    end
    
    def vxlan_addr=(value)
        @property_flush[:vxlan_addr] = value
    end

    def vxlan_ipvers=(value)
        @property_flush[:vxlan_ipvers] = value
    end
    
    def vxlan_mgroup=(value)
        @property_flush[:vxlan_mgroup] = value
    end

    def vxlan_range=(value)
        @property_flush[:vxlan_range] = value
    end
    
    ## Client side property setup: the pointer to the EVS controller ##
    def controller=(value)
        @property_flush[:controller] = value
    end

    def set_controller_property(host, property)
        begin
            evsadm("set-controlprop", host, property)
        rescue Puppet::ExecutionFailure => e
            # Pass up the exception to upper level
            raise
        end
    end

    def set_client_property(property)
        begin
            evsadm("set-prop", "-p", property)
        rescue Puppet::ExecutionFailure => e
            # Pass up the exception to upper level
            raise
        end
    end

    def flush
        case @resource[:name]
        when "controller_property"
            if @property_flush.has_key?(:controller)
                raise Puppet::Error, "controller_property does not have "\
                    "'controller' property. Try client_property"
            end
            
            props = []
            @property_flush.each do |key, value|
                # Change symbol to string
                k = key.to_s.gsub! "_", "-"
                case k
                # uplink-port property takes up to five values:
                # link, [vlan-range], [vxlan-range], [host] and [flat]
                when "uplink-port"
                    link, vlan, vxlan, host, flat = \
                        value.strip().split(";", -1)

                    # store host parameter if exists
                    host = host != "" ? ["-h", host] : []

                    # Concatenate the parameters of uplink-port
                    link = "uplink-port=#{link}"
                    vlan = vlan != "" ? ",vlan-range=#{vlan}" : ""
                    vxlan = vxlan != "" ? ",vxlan-range=#{vxlan}" : ""
                    flat = flat != "" ? ",flat=#{flat}" : ""

                    p = ["-p", "#{link}#{vlan}#{vxlan}#{flat}"]

                    props << [host, p]

                # uri-template property takes up to two values:
                # uri and [host]
                when "uri-template"
                    uri, host = value.strip().split(";", -1)
                    
                    # store host parameter if exists
                    host = host != "" ? ["-h", host] : []
                    uri = ["-p", "uri-template=#{uri}"]
                    
                    props << [host, uri]

                # vxlan_addr property takes up to three values:
                # vxlan-addr, [vxlan-range] and [host]
                when "vxlan-addr"
                    addr, range, host = value.strip().split(";", -1)
                    
                    # store host parameter if exists
                    host = host != "" ? ["-h", host] : []
                    addr = "vxlan-addr=#{addr}"
                    range = range != "" ? ",vxlan-range=#{range}" : ""
                    
                    p = ["-p", "#{addr}#{range}"]
                    
                    props << [host, p]

                # l2-type, vlan-range, vxlan-range, vxlan-ipvers
                # and vxlan-mgroup properties just need values
                else
                    host = []
                    p = ["-p", "#{k}=#{value}"]
                    props << [host, p]
                end
            end

            # Reverse the array so that l2-type, vlan-range, vxlan-range
            # vxlan-ipvers and vxlan-mgroups are set before the others
            props.reverse!
            # iteratively set controller property
            props.each do |p|
                begin
                    set_controller_property(p[0], p[1])
                # Do not terminate the script even if there is an error
                # Just continue to next script
                rescue Puppet::ExecutionFailure => e
                    Puppet.err "Cannot apply the property: \n#{e.inspect}"
                end
            end

        when "client_property"
            unless @property_flush.has_key?(:controller)
                raise Puppet::Error,
                    "'controller' property must be specified"
            end
            prop = "controller=#{@property_flush[:controller]}"
            begin
                set_client_property(prop) 
            rescue Puppet::ExecutionFailure => e
                raise Puppet::Error, "Cannot apply the property:\n #{e.inspect}"
            end
        end
        
        # Synchronize all the SHOULD values to IS values
        @property_hash = resource.to_hash
    end
end

