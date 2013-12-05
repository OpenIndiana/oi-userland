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
#
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#

# Standard prolog
#
. /lib/svc/share/smf_include.sh
. /lib/svc/share/net_include.sh

EXECFILE="/usr/lib/inet/ptpd"

if [ -z $SMF_FMRI ]; then
        echo "SMF framework variables are not initialized."
        exit $SMF_EXIT_ERR_NOSMF
fi

#
# get_prop fmri propname
#
get_prop () {
	VALUE="`$SVCPROP -cp config/$1 $SMF_FMRI 2>/dev/null`"
	# Empty astring_list values show up as "" - do not return this.
	if [ "$VALUE" != "\"\"" ]; then
		echo $VALUE
	fi
}

errlog () {
	echo $1 >&2
}

#Do not refresh IGMP group
CMD_LINE_ARGS=" -j"

LISTEN_IFNAME="`get_prop listen_ifname`"
if [  -n "$LISTEN_IFNAME" ]; then
		CMD_LINE_ARGS="$CMD_LINE_ARGS -b $LISTEN_IFNAME"
fi

NODE_TYPE="`get_prop node_type`"
if [ -n "$NODE_TYPE" ]; then
	if [ "$NODE_TYPE" = "master" ]; then
		CMD_LINE_ARGS="$CMD_LINE_ARGS -W"
	elif [ "$NODE_TYPE" = "slave" ]; then
		CMD_LINE_ARGS="$CMD_LINE_ARGS -g"
	else
		errlog "node_type needs to be either slave or master. See ptp (1M). Exiting."
		exit $SMF_EXIT_ERR_CONFIG
	fi
else
	CMD_LINE_ARGS="$CMD_LINE_ARGS -g"
fi

USE_HW="`get_prop use_hw`"
if [ "$USE_HW" = "true" ];then
	CMD_LINE_ARGS="$CMD_LINE_ARGS -K"
fi

DOMAIN="`get_prop domain`"
if [ "$DOMAIN" -gt 0 -a "$DOMAIN" -lt 4 ]; then
	CMD_LINE_ARGS="$CMD_LINE_ARGS -i $DOMAIN"
fi

ANN_INTVL="`get_prop announce_interval`"
if [ "$ANN_INTVL" -gt 0 -a "$ANN_INTVL" -ne 2 ]; then
	CMD_LINE_ARGS="$CMD_LINE_ARGS -n $ANN_INTVL"
fi

SYNC_INTVL="`get_prop sync_interval`"
if [ "$SYNC_INTVL" -gt 0 -a "$SYNC_INTVL" -ne 1 ]; then
	CMD_LINE_ARGS="$CMD_LINE_ARGS -y $SYNC_INTVL"
fi

LOGFILE="`get_prop logfile`"
if [ -n "$LOGFILE" -a "$LOGFILE" != "/var/log/ptp.log" ]; then
	CMD_LINE_ARGS="$CMD_LINE_ARGS -f $LOGFILE"
fi

OTHER_OPTIONS="`get_prop other_options`"
if [ -n "$OTHER_OPTIONS" ]; then
	CMD_LINE_ARGS="$CMD_LINE_ARGS $OTHER_OPTIONS"
fi


# start ptp daemon
$EXECFILE $CMD_LINE_ARGS
exit $SMF_EXIT_OK
