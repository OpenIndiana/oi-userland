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

Puppet::Type.type(:ip_interface).provide(:ip_interface) do
    desc "Provider for management of IP interfaces for Oracle Solaris"
    confine :operatingsystem => [:solaris]
    defaultfor :osfamily => :solaris, :kernelrelease => ['5.11', '5.12']
    commands :ipadm => '/usr/sbin/ipadm', :dladm => '/usr/sbin/dladm'

    def self.instances
        (dladm("show-link", "-p", "-o", "link").split("\n") &
         ipadm("show-if", "-p", "-o", "ifname").split("\n")).collect do |ifname|
            new(:name => ifname,
                :ensure => :present)
        end
    end

    def add_options
       options = []
       if @resource[:temporary] == :true
         options << "-t"
       end
       options
    end

    def exists?
        ipadm("show-if", "-p", "-o", "IFNAME").split(
              "\n").include? @resource[:name]
    end

    def create
        ipadm('create-ip', add_options, @resource[:name])
    end

    def destroy
        ipadm('delete-ip', @resource[:name])
    end
end
