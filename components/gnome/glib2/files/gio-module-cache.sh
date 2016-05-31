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

NEED_COMPILE=0
MODULE_DIR_32="/usr/lib/gio/modules"
MODULE_DIR_64="/usr/lib/64/gio/modules"
CACHE_FILE_32="${MODULE_DIR_32}/giomodule.cache"
CACHE_FILE_64="${MODULE_DIR_64}/giomodule.cache"

if [[ ! -r "${CACHE_FILE_32}" ]] ; then
	# Need to create initial file
	NEED_COMPILE=1
elif [[ ! -r "${CACHE_FILE_64}" ]] ; then
	# Need to create initial file
	NEED_COMPILE=1
elif [[ "${MODULE_DIR_32}" -nt "${CACHE_FILE_32}" ]] ; then
	# Directory has been updated - file may have been added or removed
	NEED_COMPILE=1
elif [[ "${MODULE_DIR_64}" -nt "${CACHE_FILE_64}" ]] ; then
	# Directory has been updated - file may have been added or removed
	NEED_COMPILE=1
elif [[ -n "$(find ${MODULE_DIR_32} -newer ${CACHE_FILE_32})" ]] ; then
	# At least one file has been updated
	NEED_COMPILE=1
elif [[ -n "$(find ${MODULE_DIR_64} -newer ${CACHE_FILE_64})" ]] ; then
	# At least one file has been updated
	NEED_COMPILE=1
fi

if [[ "${NEED_COMPILE}" -ne 0 ]] ; then
	umask 022
	/usr/bin/gio-querymodules "${MODULE_DIR_32}"
	result=$?
	if [[ $result -ne 0 ]] ; then
		print "/usr/bin/gio-querymodules failed with exit code $result"
		exit $SMF_EXIT_ERR_FATAL
	fi
	if [[ ! -r "${CACHE_FILE_32}" ]] ; then
		exit $SMF_EXIT_ERR_FATAL
	fi
	# Since gio-querymodules renames the result into place, update
	# the file mtime after moving so it matches the directory mtime.
	touch -c -r "${MODULE_DIR_32}" "${CACHE_FILE_32}"

	/usr/bin/64/gio-querymodules "${MODULE_DIR_64}"
	result=$?
	if [[ $result -ne 0 ]] ; then
		print "/usr/bin/64/gio-querymodules failed with exit code $result"
		exit $SMF_EXIT_ERR_FATAL
	fi
	if [[ ! -r "${CACHE_FILE_64}" ]] ; then
		exit $SMF_EXIT_ERR_FATAL
	fi
	touch -c -r "${MODULE_DIR_64}" "${CACHE_FILE_64}"
fi

exit $SMF_EXIT_OK
