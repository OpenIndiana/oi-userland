#!/bin/bash
#
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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
#

unset LD_LIBRARY_PATH
unset LD_LIBRARY_PATH_32
unset LD_LIBRARY_PATH_64
unset LD_PRELOAD
unset LD_PRELOAD_32
unset LD_PRELOAD_64

export TOPDIR="../../"
export DO_CLEANUP="no"
export DO_MAKE="no"

UNKNOWN_ARG=no
PRINT_HELP=no

check_args() {
	while [ "$#" -gt 0 ] ; do
		UNKNOWN_ARG=no
		case "$1" in
		--cleanup)
			DO_CLEANUP=yes
		;;
		--make)
			DO_MAKE=yes
		;;
		*)
			UNKNOWN_ARG=yes
		;;
		esac

		if [ "${UNKNOWN_ARG}" = "yes" ] ; then
			echo "$1: Invalid argument"
			PRINT_HELP=yes
			shift
			continue
		fi

		shift
	done

	export DO_CLEANUP DO_MAKE TOPDIR

	if [ "$PRINT_HELP" = "yes" ] || [ "$UNKNOWN_ARG" = "yes" ] ; then
		echo "Usage: `basename $0` [ --cleanup ] [ --make ]"
		exit 1
	fi
}

run_make() {
	if [ "${DO_MAKE}" = "no" ] ; then
		return
	fi

	for file in \
		"18.limits.stdcxx-436" \
		"18.limits.traps.stdcxx-624" \
		"20.specialized.stdcxx-390" \
		"21.string.append.stdcxx-438" \
		"21.string.io.stdcxx-206" \
		"21.string.io.stdcxx-250" \
		"21.string.replace.stdcxx-175" \
		"21.string.stdcxx-162" \
		"21.string.stdcxx-231" \
		"21.string.stdcxx-466" \
		"22.locale.codecvt.stdcxx-435" \
		"22.locale.cons.stdcxx-485" \
		"22.locale.messages.stdcxx-542" \
		"22.locale.money.get.stdcxx-62" \
		"22.locale.num.put.stdcxx-2" \
		"22.locale.stdcxx-554" \
		"23.associative.stdcxx-16" \
		"23.bitset.cons.stdcxx-297" \
		"23.deque.special.stdcxx-127" \
		"23.list.cons.stdcxx-268" \
		"23.list.insert.stdcxx-331" \
		"23.list.special.stdcxx-334" \
		"23.set.stdcxx-216" \
		"23.vector.bool.stdcxx-235" \
		"23.vector.stdcxx-611" \
		"24.istream.iterator.cons.stdcxx-645" \
		"24.istream.iterator.ops.stdcxx-321" \
		"24.operations.stdcxx-234" \
		"26.valarray.binary.stdcxx-237" \
		"26.valarray.members.stdcxx-313" \
		"26.valarray.members.stdcxx-318" \
		"26.valarray.sub.stdcxx-224" \
		"26.valarray.sub.stdcxx-309" \
		"26.valarray.sub.stdcxx-448" \
		"26.valarray.transcend.stdcxx-315" \
		"26.valarray.unary.stdcxx-314" \
		"27.basic.ios.copyfmt.stdcxx-766" \
		"27.basic.ios.tie.stdcxx-804" \
		"27.cstdio.stdcxx-195" \
		"27.filebuf.members.stdcxx-308" \
		"27.filebuf.virtuals.stdcxx-522" \
		"27.ostream.unformatted.stdcxx-626" \
		"27.streambuf.imbue.stdcxx-307" \
		"27.stringbuf.members.stdcxx-427" \
		"27.stringbuf.overflow.stdcxx-795" \
		"27.stringbuf.str.stdcxx-514" \
		"27.stringbuf.xsputn.stdcxx-515" \
		"27.stringbuf.xsputn.stdcxx-576"
	do
		if [ -f "${file}.o" ] ; then
			rm -f ${file}.o
		fi
		if [ -f "${file}" ] ; then
			rm -f ${file}
		fi

		gmake ${file}
	done
}

do_cleanup() {
	if [ "${DO_CLEANUP}" = "no" ] ; then
		return
	fi

	for file in \
		"18.limits.stdcxx-436" \
		"18.limits.traps.stdcxx-624" \
		"20.specialized.stdcxx-390" \
		"21.string.append.stdcxx-438" \
		"21.string.io.stdcxx-206" \
		"21.string.io.stdcxx-250" \
		"21.string.replace.stdcxx-175" \
		"21.string.stdcxx-162" \
		"21.string.stdcxx-231" \
		"21.string.stdcxx-466" \
		"22.locale.codecvt.stdcxx-435" \
		"22.locale.cons.stdcxx-485" \
		"22.locale.messages.stdcxx-542" \
		"22.locale.money.get.stdcxx-62" \
		"22.locale.num.put.stdcxx-2" \
		"22.locale.stdcxx-554" \
		"23.associative.stdcxx-16" \
		"23.bitset.cons.stdcxx-297" \
		"23.deque.special.stdcxx-127" \
		"23.list.cons.stdcxx-268" \
		"23.list.insert.stdcxx-331" \
		"23.list.special.stdcxx-334" \
		"23.set.stdcxx-216" \
		"23.vector.bool.stdcxx-235" \
		"23.vector.stdcxx-611" \
		"24.istream.iterator.cons.stdcxx-645" \
		"24.istream.iterator.ops.stdcxx-321" \
		"24.operations.stdcxx-234" \
		"26.valarray.binary.stdcxx-237" \
		"26.valarray.members.stdcxx-313" \
		"26.valarray.members.stdcxx-318" \
		"26.valarray.sub.stdcxx-224" \
		"26.valarray.sub.stdcxx-309" \
		"26.valarray.sub.stdcxx-448" \
		"26.valarray.transcend.stdcxx-315" \
		"26.valarray.unary.stdcxx-314" \
		"27.basic.ios.copyfmt.stdcxx-766" \
		"27.basic.ios.tie.stdcxx-804" \
		"27.cstdio.stdcxx-195" \
		"27.filebuf.members.stdcxx-308" \
		"27.filebuf.virtuals.stdcxx-522" \
		"27.ostream.unformatted.stdcxx-626" \
		"27.streambuf.imbue.stdcxx-307" \
		"27.stringbuf.members.stdcxx-427" \
		"27.stringbuf.overflow.stdcxx-795" \
		"27.stringbuf.str.stdcxx-514" \
		"27.stringbuf.xsputn.stdcxx-515" \
		"27.stringbuf.xsputn.stdcxx-576"
	do
		rm -f "${file}"
	done
}

check_args $@
run_make
do_cleanup

exit 0

