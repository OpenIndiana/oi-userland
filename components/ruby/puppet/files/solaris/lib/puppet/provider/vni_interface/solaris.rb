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

Puppet::Type.type(:vni_interface).provide(:vni_interface) do
    desc "Provider for management of VNI interfaces for Oracle Solaris"
    confine :operatingsystem => [:solaris]
    defaultfor :osfamily => :solaris, :kernelrelease => ['5.11', '5.12']
    commands :ipadm => '/usr/sbin/ipadm'

    def self.instances
        vnis = []
        ipadm("show-if", "-p", "-o", "IFNAME,CLASS").split(
              "\n").each do |line|
            ifname, ifclass = line.split(":", 2)
            next if ifclass != "vni"
            vnis << new(:name => ifname, :ensure => :present)
        end
        vnis
    end

    def add_options
       options = []
       if @resource[:temporary] == :true
         options << "-t"
       end
       options
    end

    def exists?
        p = exec_cmd(command(:ipadm), "show-if", "-p", "-o", "IFNAME,CLASS",
                     @resource[:name])
        if p[:exit] == 1
            return false
        end

        ifname, ifclass = p[:out].strip().split(":", 2)
        if ifclass == "vni"
            return true
        end

        # for all other cases, return false
        return false
    end

    def create
        ipadm('create-vni', add_options, @resource[:name])
    end

    def destroy
        ipadm('delete-vni', @resource[:name])
    end

    def exec_cmd(*cmd)
        output = Puppet::Util::Execution.execute(cmd, :failonfail => false)
        {:out => output, :exit => $CHILD_STATUS.exitstatus}
    end
end
