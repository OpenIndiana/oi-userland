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

Puppet::Type.newtype(:evs_properties) do
    @doc = "Manage global properties of EVS(Elastic Virtual Switch) for both 
            client and controller. There are two instances associated with 
            contoller and client properties respectively"
    
    ## This is a property setter, thus not ensurable ##
    newparam(:name) do
        desc "Type of properties\n"\
            "Names are preset to 'controller_property' and 'client_property'"
        # Validate the name:
        # Names are preset to "controller_property" and "client_property"
        validate do |value|
            if value != "controller_property" && value != "client_property"
                raise Puppet::Error, "Invalid property type name\n" \
                    "Name must be either 'controller_property' or " \
                    "'client_property'"
            end
        end
    end
    
    ## Properties associated with "controller_property" ##
    ## All the properties are read/write
    newproperty(:l2_type) do
        desc "Define how an EVS will be implemented across machines "\
            "(controller_property)"
        newvalues("vlan", "vxlan", "flat", "")
    end
    
    newproperty(:uplink_port) do
        desc "Specifies the datalink to be used for VLANs or VXLANs "\
            "(controller_property)\n"\
            "uplink_port value must be in the format of either\n"\
            "uplink_port=<uplink>  or \n"\
            "uplink_port='<uplink>;[<vlan-range>];[<vxlan-range>];"\
            "[<host>];[<flat>]'"
        # Use munge to support single value input
        munge do |value|
            uplink_list = value.strip().split(";", -1)
            if uplink_list.length == 0
                value = ";;;;"
            elsif uplink_list.length == 1
                value = "#{value};;;;"
            elsif uplink_list.length == 5
                value
            else
                raise Puppet::Error, "Invalid uplink_port format: \n" \
                    "The format must be uplink_port=<uplink> or " \
                    "uplink_port='<uplink>;[<vlan-range>];[<vxlan-range>];" \
                    "[<host>];[<flat>]'"
            end
        end
    end
    
    newproperty(:uri_template) do
        desc "URI for per-EVS Node RAD Connection (controller_property)\n"\
            "The syntax of the uri_template value will be of the form:\n"\
            "uri_template='ssh://[username@][;<host>]' or \n"\
            "uri_template='unix://[username@][;<host>]'"
        # Use munge to support single value input
        munge do |value|
            uri_list = value.strip().split(";", -1)
            if uri_list.length == 0
                value = ";"
            elsif uri_list.length == 1
                value = "#{value};"
            elsif uri_list.length == 2
                value
            else
                raise Puppet::Error, "Invalid uri_template format: \n"\
                    "The format of the uri_template value must be\n"\
                    "uri_template='ssh://[username@][;<host>]' or \n"\
                    "uri_template='unix://[username@][;<host>]'"
            end
        end
    end
    

    newproperty(:vlan_range) do
        desc "List of VLAN ID ranges that will be used for creating EVS "\
            "(controller_property)\n"\
            "The maximum valid range is 1-4094"
    end

    newproperty(:vxlan_addr) do
        desc "IP address on top of which VXLAN datalink should be created "\
            "(controller_property)\n"\
            "The syntax of the vxlan_addr value will be of the form:\n"\
            "vxlan_addr=<vxlan_IP_addr> or"\
            "vxlan_addr='<vxlan_IP_addr>;[<vxlan-range>];[<host>]'"
        # Use munge to support single value input
        munge do |value|
            vxlan_list = value.strip().split(";", -1)
            if vxlan_list.length == 0
                value = ";;"
            elsif vxlan_list.length == 1
                value = "#{value};;"
            elsif vxlan_list.length == 3
                value
            else
                raise Puppet::Error, "Invalid vxlan_addr format: \n" \
                    "The format of the vxlan_addr value must be\n"\
                    "vxlan_addr=<vxlan_IP_addr> or"\
                    "vxlan_addr='<vxlan_IP_addr>;[<vxlan-range>];[<host>]'"
            end
        end
    end

    newproperty(:vxlan_ipvers) do
        desc "IP version of the address for VXLAN datalinks "\
            "(controller_property)"
    end

    newproperty(:vxlan_mgroup) do
        desc "Multicast address that needs to be used while creating VXLAN" \
            " links (controller_property)"
    end

    newproperty(:vxlan_range) do
        desc "List of VXLAN ID ranges that will be used for creating EVS "\
            "(controller_property)\n"\
            "The maximum valid range is 0-16777215"
    end
    
    
    ### The read/write property associated with "client_property" ###
    newproperty(:controller) do
        desc "SSH address of EVS controller server (client_property)"
    end
end
