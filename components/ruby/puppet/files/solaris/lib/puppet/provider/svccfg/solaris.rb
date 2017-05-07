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
            # if the property group or property doesn't exist at all, the exit
            # code will be 1
            return false if p[:exit] != 0

            # turn @resource[:value] into a simple string by dropping the first
            # and last array elements (the parens) and removing all double
            # quotes
            simple = @resource[:value][1..-2].join(" ")[1..-2].gsub(/\"/, "")

            # For properties, check the value against what's in SMF.  For
            # property groups, svcprop already verified the PG exists by not
            # failing
            if @resource[:property].include? "/"
                return p[:out].strip == simple
            else
                return p[:exit] == 0
            end
        end
    end

    def create
        # Check to see if the service instance exists
        cmd = Array[command(:svccfg), "select", @resource[:fmri]]
        svc_exist = exec_cmd(cmd)

        # Raise an error if the entity does not exist
        if svc_exist[:exit] != 0
            raise Puppet::Error, "SMF entity #{@resource[:fmri]} does not exist"
        end
        
        args = ["-s", @resource[:fmri]]

        if @resource[:property].include? "/"
            args << "setprop" << @resource[:property] << "="
            if type = @resource[:type] and type != nil
                args << @resource[:type] + ":"
            end
            args << @resource[:value]
        else
            args << "addpg" << @resource[:property] << @resource[:type]
        end
        svccfg(args)
        svccfg("-s", @resource[:fmri], "refresh")
    end

    def destroy
        if @resource[:property].include? "/"
            svccfg("-s", @resource[:fmri], "delprop", @resource[:property])
        else
            svccfg("-s", @resource[:fmri], "delpg", @resource[:property])
        end
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
