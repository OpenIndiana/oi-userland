#!/bin/sh

#
# Make sure TUN/TAP device nodes are present. This may be not needed
# if clients such as OpenVPN are running in the global zone and so
# tickle initialization of the drivers, but seems to be needed when
# clients are only in local zones that use `device match` attribute
# to get their pipes to `/dev/tun` and `/dev/tap`.
# This can be used as either init-script or an SMF service method.
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
# Copyright 2016 Jim Klimov
#

do_start() {
    /usr/sbin/add_drv tun
    /usr/sbin/add_drv tap
}

do_stop() {
    /usr/sbin/rem_drv tun
    /usr/sbin/rem_drv tap
}

do_status() {
    modinfo | egrep ' (tun|tap) '
}


case "$1" in
    stop) do_stop;;
    #start) do_start;;
    start|restart) do_stop; sleep 5; do_start; do_status;;
    status) do_status;;
esac
