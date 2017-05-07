#!/sbin/sh
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
# Copyright (c) 2008, 2012, Oracle and/or its affiliates. All rights reserved.
#

. /lib/svc/share/smf_include.sh

# SMF_FMRI is the name of the target service. This allows multiple instances 
# to use the same script.

if [ -z "$SMF_FMRI" ]; then
	echo "SMF framework variables are not initialized."
	exit $SMF_EXIT_ERR
fi

tcsd_start() 	{
	echo /usr/lib/64/tcsd 
	/usr/lib/64/tcsd >/dev/null 2>&1 &
}
	
tcsd_stop()	{
	/usr/bin/pkill -x tcsd >/dev/null 2>&1
}

case "$1" in
'start')
	tcsd_start 
	;;

'stop')
	tcsd_stop
	;;


*)
	echo "Usage: $0 {start|stop}"
	exit 1
	;;

esac
exit $SMF_EXIT_OK
