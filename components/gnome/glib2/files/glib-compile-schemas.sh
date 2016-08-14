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
SCHEMA_DIR='/usr/share/glib-2.0/schemas'
COMPILED_FILE="${SCHEMA_DIR}/gschemas.compiled"

if [[ ! -r "${COMPILED_FILE}" ]] ; then
	# Need to create initial file
	NEED_COMPILE=1
elif [[ "${SCHEMA_DIR}" -nt "${COMPILED_FILE}" ]] ; then
	# Directory has been updated - file may have been added or removed
	NEED_COMPILE=1
elif [[ -n "$(find ${SCHEMA_DIR} -newer ${COMPILED_FILE})" ]] ; then
	# At least one file has been updated
	NEED_COMPILE=1
fi

if [[ "${NEED_COMPILE}" -ne 0 ]] ; then
	umask 022
	/usr/bin/glib-compile-schemas "${SCHEMA_DIR}" 2>&1
	result=$?
	if [[ $result -ne 0 ]] ; then
		print "glib-compile-schemas failed with exit code $result"
		exit $SMF_EXIT_ERR_FATAL
	fi
	if [[ ! -r "${COMPILED_FILE}" ]] ; then
		if [[ -n "$(find ${SCHEMA_DIR} -name '*.gschema.xml')" ]] ; then
			exit $SMF_EXIT_ERR_FATAL
		fi
	else
	# Since glib-compile-schemas renames the result into place, update
	# the file mtime after moving so it matches the directory mtime.
		touch -c -r "${SCHEMA_DIR}" "${COMPILED_FILE}"
	fi
fi

exit $SMF_EXIT_OK
