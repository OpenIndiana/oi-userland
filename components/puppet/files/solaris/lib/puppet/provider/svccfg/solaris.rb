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

Puppet::Type.type(:svccfg).provide(:svccfg) do
    desc "Provider for svccfg actions on Oracle Solaris"
    defaultfor :operatingsystem => :solaris
    commands :svccfg => "/usr/sbin/svccfg", :svcprop => "/usr/bin/svcprop"

    def exists?
        p = exec_cmd(command(:svcprop), "-p", @resource[:property],
                     @resource[:fmri])
        if @resource[:ensure] == :absent
            # only test for the existance of the property and not the value
            return p[:exit] == 0
        elsif @resource[:ensure] == :present
            # if the property doesn't exist at all, the exit code will be 1
            return false if p[:exit] != 0

            # strip the leading and trailing parens if resource[:property]
            # contains a slash as this indicates that a value is associated
            # with it.
            if @resource[:property].include? "/"
                return p[:out].strip == \
                    @resource[:value][1..-2].join(" ")[1..-2]
            end
            # resource[:property] is a property group, not a property.
            # There is no value to manipulate, but the property needs to be
            # created, so return true.
            return p[:exit] == 0
        end
    end

    def create
        # Check to see if the service instance exists
        cmd = Array[command(:svccfg), "select", @resource[:fmri]]
        svc_exist = exec_cmd(cmd)

        # Create the service instance if it doesn't exist
        if svc_exist[:exit] != 0
            service, instance = \
                @resource[:fmri].split(":").reject{|n| n == "svc"}
            svccfg("-s", service, "add", instance)
        end

        # Add the property
        if @resource[:property].include? "/"
            svccfg("-s", @resource[:fmri], "setprop", @resource[:property],
                   "=", @resource[:type] + ":", @resource[:value])
        else
            svccfg("-s", @resource[:fmri], "addpg", @resource[:property],
                   @resource[:type])
        end
        svccfg("-s", @resource[:fmri], "refresh")
    end

    def destroy
        svccfg("-s", @resource[:fmri], "delprop", @resource[:property])
        svccfg("-s", @resource[:fmri], "refresh")
    end

    def delcust
        list_cmd = Array[command(:svccfg), "-s", @resource[:fmri], "listprop",
                         "-l", "admin"]
        delcust_cmd = Array[command(:svccfg), "-s", @resource[:fmri]]
        if @resource[:property] != nil
            list_cmd += Array[@resource[:property]]
            delcust_cmd += Array[@resource[:property]]
        end

        # look for any admin layer customizations for this entity
        p = exec_cmd(list_cmd)
        if p[:out].strip != ''
            # there are admin customizations
            if @resource[:property] == nil
                svccfg("-s", @resource[:fmri], "delcust")
            else
                svccfg("-s", @resource[:fmri], "delcust", @resource[:property])
            end
            svccfg("-s", @resource[:fmri], "refresh")
        end
    end

    def exec_cmd(*cmd)
        output = Puppet::Util::Execution.execute(cmd, :failonfail => false)
        {:out => output, :exit => $CHILD_STATUS.exitstatus}
    end
end
