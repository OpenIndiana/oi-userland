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
# Copyright (c) 2009, 2011, Oracle and/or its affiliates. All rights reserved.
#

# Standard prolog
#
. /lib/svc/share/smf_include.sh

if [ -z $SMF_FMRI ]; then
        echo "SMF framework variables are not initialized."
        exit $SMF_EXIT_ERR
fi

#
# Is NTP configured?
#
if [ ! -f /etc/inet/ntp.conf ]; then
	echo "Error: Configuration file '/etc/inet/ntp.conf' not found." \
	    "  See ntpd(1M)."
	exit $SMF_EXIT_ERR_CONFIG
fi

# Disable globbing to prevent privilege escalations by users authorized
# to set property values for the NTP service.
set -f 

#
# Build the command line flags
#
shift $#
set -- -p /var/run/ntp.pid
# We allow a step larger than the panic value of 17 minutes only 
# once when ntpd starts up. If always_all_large_step is true, 
# then we allow this each time ntpd starts. Otherwise, we allow
# it only the very first time ntpd starts after a boot. We 
# check that by making ntpd write its pid to a file in /var/run.

val=`svcprop -c -p config/always_allow_large_step $SMF_FMRI`
if [ "$val" = "true" ] || \
    [ ! -f /var/run/ntp.pid ]; then
        set -- "$@" -g
fi

# Auth was off by default in xntpd now the default is on. Better have a way
# to turn it off again. Also check for the obsolete "authentication" keyword.
val=`svcprop -c -p config/no_auth_required $SMF_FMRI`
if [ ! "$val" = "true" ]; then
        val=`/usr/bin/nawk '/^[ \t]*#/{next}
            /^[ \t]*authentication[ \t]+no/ {
                printf("true", $2)
                next } ' /etc/inet/ntp.conf`
fi
[ "$val" = "true" ] && set -- "$@" --authnoreq

# Set up logging if requested.
logfile=`svcprop -c -p config/logfile $SMF_FMRI`
val=`svcprop -c -p config/verbose_logging $SMF_FMRI`
[ "$val" = "true" ] && [ -n "$logfile" ]  && set -- "$@" -l $logfile

# Register with mDNS.
val=`svcprop -c -p config/mdnsregister $SMF_FMRI`
mdns=`svcprop -c -p general/enabled svc:/network/dns/multicast:default`
[ "$val" = "true" ] && [ "$mdns" = "true" ] && set -- "$@" -m

# We used to support the slewalways keyword, but that was a Sun thing
# and not in V4. Look for "slewalways yes" and set the new slew option.
slew_always=`svcprop -c -p config/slew_always $SMF_FMRI`
if [ ! "$slew_always" = "true" ]; then
       slew_always=`/usr/bin/nawk '/^[ \t]*#/{next}
	    /^[ \t]*slewalways[ \t]+yes/ {
        	printf("true", $2)
        	next } ' /etc/inet/ntp.conf`
fi
[ "$slew_always" = "true" ] && set -- "$@" --slew

# Set up debugging.
deb=`svcprop -c -p config/debuglevel $SMF_FMRI`

# If slew_always is set to true, then the large offset after a reboot
# might take a very long time to correct the clock. Optionally allow
# a step once after a reboot if slew_always is set when allow_step_at_boot
# is also set. 
val=`svcprop -c -p config/allow_step_at_boot $SMF_FMRI`
if [ "$val" = "true" ] && [ "$slew_always" = "true" ] && \
    [ ! -f /var/run/ntp.pid ]; then
       set -- "$@" --force-step-once
fi

# Start the daemon. If debugging is requested, put it in the background, 
# since it won't do it on it's own.
if [ "$deb" -gt 0 ]; then
	/usr/lib/inet/ntpd "$@" --set-debug-level=$deb >/var/ntp/ntp.debug &
else
	/usr/lib/inet/ntpd "$@"
fi

# Now, wait for the first sync, if requested.
val=`svcprop -c -p config/wait_for_sync $SMF_FMRI`
[ "$val" = "true" ] && /usr/lib/inet/ntp-wait

exit $SMF_EXIT_OK
