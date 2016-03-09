#!/bin/sh
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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

# proxy_cvs.sh 
# script tunnels cvs+ssh through http proxy outside of ORAWAN.  It's easy to
# tell cvs to use ssh instead of rsh, just set 'CVS_RSH=ssh'. It's lot harder
# to tell ssh running on cvs behalf to use http proxy. So our approach is to
# create temp script, which executes ssh with all proxy parameters to set up
# HTTP tunnel for ssh session.
#
# If `http_proxy` variable is not set the script uses a default proxy,
# which is 'emeacache.uk.oracle.com:80'.
#
# All arguments, which appear on command line are passed to cvs(1) command with
# out any modification.
#
# Example:
# To check out pflogd sources from OpenBSD repository to local pflogd.src
# directory one invokes proxy_cvs.sh like that:
#
#	proxy_cvs.sh -qd anoncvs@anoncvs.ca.openbsd.org:/cvs	\
#		-d pflogd.src src/sbin/pflogd
#
# To check a particular version of pflogd sources, one has to use a
# corresponding CVS version tag assigned by upstream developers. Command below
# retrieves pflogd source code released by OpenBSD 5.4:
#
#	proxy_cvs.sh -qd anoncvs@anoncvs.ca.openbsd.org:/cvs	\
#		-rOPENBSD_5_4 -d pflogd.src src/sbin/pflogd
#

#
# crate_ssh_wrapper
# function creates a shell script, which a netcat(1) as proxy to tunnel
# ssh via http proxy.
#
# Arguments:
#	file name where to dump script, function makes file executable.
#
function create_ssh_wraper
{
	if [ -z "$http_proxy" ] ; then
		HTTP_PROXY='emeacache.uk.oracle.com:80'
	else
		HTTP_PROXY=$http_proxy
	fi
	echo '#!/bin/sh\n' > $1
	echo 'ssh -oProxyCommand='"'/usr/bin/nc -X connect -x $HTTP_PROXY %h %p'"\
	    '-oStrictHostKeyChecking=no -oUserKnownHostsFile=/dev/null $*' >> $1
	chmod +x $1
}

#
# This is a workaround. I don't know how to pass all arguments required by
# 'ssh/http' proxy into CVS_RSH environment variable. So my solution is to
# dump desired arguments into a temporary shell script and point CVS_RSH
# variable to it.
#
function init_cvs_rsh
{
	export TMPF=`mktemp`
	create_ssh_wraper $TMPF;
	CVS_RSH=$TMPF
	export CVS_RSH
}

init_cvs_rsh

trap "rm -f $TMPF" EXIT

cvs $*

RETURN=$?

exit $RETURN
