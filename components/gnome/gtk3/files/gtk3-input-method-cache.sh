#! /bin/ksh93

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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

PATH=/usr/bin:/usr/sbin

. /lib/svc/share/smf_include.sh

USAGE="Usage: $0 <method>"

if [[ $# -ne 1 ]] ; then
	print "$USAGE" >&2
	exit 2
fi

METHOD="$1"

case $METHOD in
	start|refresh)
		# Continue with rest of script
		;;
	-*)
		print "$USAGE" >&2
		exit 2
		;;
	*)
		print "Invalid method $METHOD" >&2
		exit 2
		;;
esac

for DIR in "" "/64"; do
    MAKE_CACHE="/usr/bin$DIR/gtk-query-immodules-3.0"
    MODULE_DIR="/usr/lib$DIR/gtk-3.0/3.0.0/immodules/"
    CACHE_FILE="/usr/lib$DIR/gtk-3.0/3.0.0/immodules.cache"

    if [[ ! -x "${MAKE_CACHE}" ]] ; then
	print "${MAKE_CACHE} not installed"
	continue
    fi

    if [[ ! -r "${CACHE_FILE}" ]]; then
	RESULT="no cache file"
    elif [[ "${METHOD}" == "refresh" ]]; then
	RESULT="refresh requested"
    elif [[ "${MODULE_DIR}" -nt "${CACHE_FILE}" ]] ; then
	RESULT="directory updated"
    else
	RESULT="$(find ${MODULE_DIR} -newer ${CACHE_FILE})"
    fi

    if [[ -n "$RESULT" ]]; then
	print "updating/creating im modules cache file ($RESULT)"
	umask 022
	${MAKE_CACHE} --update-cache
	if [ $? -ne 0 ]; then
	    print "${MAKE_CACHE} exited with an error while generating the cache file ${CACHE_FILE}"
	    exit $SMF_EXIT_ERR_FATAL
	else
	    print "input method cache installed in ${CACHE_FILE}"
	fi
    fi
done

exit $SMF_EXIT_OK
