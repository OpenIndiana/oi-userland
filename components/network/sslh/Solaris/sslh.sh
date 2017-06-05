#!/sbin/sh
#
#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 John Smith. All rights reserved.
#
#

# Standard prolog
#
. /lib/svc/share/smf_include.sh

#
# Is sslh configured?
#
if [ ! -f /etc/sslh.cfg ]; then
	echo "Error: Configuration file '/etc/sslh.cfg' not found." \
	    "  See sslh(8)."
	exit $SMF_EXIT_ERR_CONFIG
fi

PIDFILE=$(grep -i pid /etc/sslh.cfg | cut -d'"' -f2)

_start() {
   if [ -f $PIDFILE ]; then
      echo "Error: Already running or pid file still present."
      exit $SMF_EXIT_ERR_FATAL
   fi
   /usr/sbin/sslh -F/etc/sslh.cfg
}

_stop() {
   if [ -f $PIDFILE ]; then
      SSLHPID=$(cat $PIDFILE)
      echo "PID: $SSLHPID"
      kill -TERM "$SSLHPID"
      [ $? = 0 ] && rm -f "$PIDFILE"
   else
      exit $SMF_EXIT_ERR_FATAL
   fi
}

case "$1" in
'start')
   _start
   ;;
'stop')
   _stop
   ;;
'refresh')
   _stop
   _start
   ;;
*)
   echo $"Usage: $0 {start|stop|refresh}"
   exit 1
   ;;
esac
exit $SMF_EXIT_OK
