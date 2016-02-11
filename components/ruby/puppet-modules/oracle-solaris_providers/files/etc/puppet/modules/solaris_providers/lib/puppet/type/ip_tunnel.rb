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

Puppet::Type.newtype(:ip_tunnel) do
    @doc = "Manage the configuration of Oracle Solaris IP Tunnel links"

    ensurable

    newparam(:name) do
        desc "The name of the iptunnel link"
        isnamevar
    end

    newparam(:temporary)  do
        desc "Optional parameter that specifies that the IP tunnel is
              temporary.  Temporary IP tunnels last until the next reboot."
        newvalues(:true, :false)
    end

    newproperty(:tunnel_type) do
        desc "Specifies the type of tunnel to be created."
        newvalues("ipv4", "ipv6", "6to4")
    end

    newproperty(:local_address) do
        desc "IP address or hostname corresponding to the local tunnel address"
    end

    newproperty(:remote_address) do
        desc "IP address or hostname corresponding to the remote tunnel address"
    end
end
