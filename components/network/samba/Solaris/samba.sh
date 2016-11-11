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
# Copyright (c) 2009, 2013, Oracle and/or its affiliates. All rights reserved.
#

. /lib/svc/share/smf_include.sh

SAMBA_CONFIG=/etc/samba/smb.conf

NSS_STRICT_NOFORK=DISABLED; export NSS_STRICT_NOFORK

# Check if given service is working properly
check_running() {
	case "$SMF_FMRI" in
		svc:/network/winbind:*)
			# It takes some time before winbind starts to really work
			# This is infinite loop which will be killed after smf timeout
			while : ; do
				sleep 2
				PING=`/usr/bin/wbinfo --ping-dc 2>&1`
				if [ $? -eq 0 ]; then
					break
				fi
				echo "$PING"
			done
			;;
	esac
	return 0
}

case "$1" in
	start)
		if [ ! -f "$SAMBA_CONFIG" ]; then
			echo "Configuration file '$SAMBA_CONFIG' does not exist."
			exit 1
		fi

		# Command to execute is found in second and further script arguments
		shift
		eval "$@"
		check_running
		;;
	stop)
		# kill whole contract group

		# first send TERM signal and wait 30 seconds
		smf_kill_contract $2 TERM 1 30
		ret=$?
		[ $ret -eq 1 ] && exit 1

		# If there are still processes running, KILL them
		if [ $ret -eq 2 ] ; then
			smf_kill_contract $2 KILL 1
		fi
		;;
	*)
		cat <<-EOT
			Usage:
			  $0 start <command to run>
			  $0 stop <contract number to kill>
		EOT
		exit 1
		;;
esac
