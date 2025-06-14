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

#
# In February 2023 we stopped to create and update GIO module cache for 32-bit
# modules at /usr/lib/gio/modules/giomodule.cache so this file is never created
# on new installations.  However, if we are updating from an older installation
# the file could be there occupying space and possibly create confusion.
#
# So let's cleanup that.
#
# The following two lines should be removed only after there are no modules
# delivered to /usr/lib/gio/modules/ and some reasonable time passed so
# everybody already updated their installations and there is no
# /usr/lib/gio/modules lingering around.
#
rm -f /usr/lib/gio/modules/giomodule.cache
rmdir /usr/lib/gio/modules 2> /dev/null

NEED_COMPILE=0
MODULE_DIR="/usr/lib/64/gio/modules"
CACHE_FILE="${MODULE_DIR}/giomodule.cache"

if [[ ! -r "${CACHE_FILE}" ]] ; then
	# Need to create initial file
	NEED_COMPILE=1
elif [[ "${MODULE_DIR}" -nt "${CACHE_FILE}" ]] ; then
	# Directory has been updated - file may have been added or removed
	NEED_COMPILE=1
elif [[ -n "$(find ${MODULE_DIR} -newer ${CACHE_FILE})" ]] ; then
	# At least one file has been updated
	NEED_COMPILE=1
fi

if [[ "${NEED_COMPILE}" -ne 0 ]] ; then
	# In a case we uninstalled latest GIO module we need to cleanup the
	# cache file because if there are no GIO modules installed then
	# gio-querymodules below does nothing and succeeds silently.  If there
	# are GIO modules installed the cleanup is harmless because the cache
	# file will be created again by gio-querymodules call below.
	rm -f "${CACHE_FILE}"
	rmdir "${MODULE_DIR}" 2> /dev/null
	[[ -d "${MODULE_DIR}" ]] || exit $SMF_EXIT_OK

	umask 022
	/usr/bin/gio-querymodules "${MODULE_DIR}"
	result=$?
	if [[ $result -ne 0 ]] ; then
		print "/usr/bin/gio-querymodules failed with exit code $result"
		exit $SMF_EXIT_ERR_FATAL
	fi
	if [[ ! -r "${CACHE_FILE}" ]] ; then
		exit $SMF_EXIT_ERR_FATAL
	fi
	# Since gio-querymodules renames the result into place, update
	# the file mtime after moving so it matches the directory mtime.
	touch -c -r "${MODULE_DIR}" "${CACHE_FILE}"
fi

exit $SMF_EXIT_OK
