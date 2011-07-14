#!/bin/bash
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
export SRCDIR=""
export BUILDDIR=""
export MACH64=""
export IS_64_BIT="no"
export MACH=`uname -p`
export MACH64=""
export UNKNOWN_ARG="no"
export PRINT_HELP="no"
export PATH="/usr/gnu/bin:${PATH}"
unset TOPDIR

check_args() {
    while [ "$#" -gt 0 ] ; do
        UNKNOWN_ARG=no
        case "$1" in
            -m32)
	    IS_64_BIT="no"
            ;;
            -m64)
	    IS_64_BIT="yes"
            ;;
            -srcdir=*)
            SRCDIR=`echo $1 | sed "s,^-srcdir=\(.*\),\1,"`
            ;;
            -builddir=*)
            BUILDDIR=`echo $1 | sed "s,^-builddir=\(.*\),\1,"`
            ;;
            *)
            UNKNOWN_ARG="yes"
            ;;
        esac

        if [ "$UNKNOWN_ARG" = "yes" ] ; then
            echo "$1: Invalid argument"
            PRINT_HELP="yes"
            shift
            continue
        fi
        shift
    done

    export IS_64_BIT SRCDIR BUILDDIR

    if [ "x${SRCDIR}" = "x" ] || [ "x${BUILDDIR}" = "x" ] ; then
	PRINT_HELP="yes"
    fi

    if [ "${PRINT_HELP}" = "yes" ] ; then
	echo "Usage: `basename $0` [ -m32 | -m64 ]"
	echo "		[ -srcdir=<source directory> ]"
	echo "		[ -builddir=<build directory> ]"
	echo ""
	exit 1
    fi

    if [ "${MACH}" = "sparc" ] ; then
	MACH64="sparcv9"
    else
	MACH64="amd64"
    fi

    export MACH MACH64
}

clean_symlinks() {
    if [ ! -d ${BUILDDIR} ] ; then
	echo "build directory ${BUILDDIR} not found or unreadable!"
	exit 1
    fi

    if [ ! -d ${SRCDIR} ] ; then
	echo "source directory ${SRCDIR} not found or unreadable!"
	exit 1
    fi

    cd ${BUILDDIR}/etc/nls

    for file in \
	languages \
	encodings \
	countries \
	gen_list
do
    if [ -L ${file} ] ; then
	rm ${file}
    fi
done

    cd ${BUILDDIR}/build

    if [ -d nls ] ; then
	rm -rf nls
    fi
}

create_symlinks() {
    cd ${BUILDDIR}/etc/nls

    for file in \
	languages \
	encodings \
	countries \
	gen_list
do
    if [ ! -L ${file} ] ; then
	if [ -f ${SRCDIR}/etc/nls/${file} ] ; then
	    ln -sf ${SRCDIR}/etc/nls/${file}
	else
	    echo "source file ${SRCDIR}/etc/nls/${file} not found or unreadable!"
	fi
    fi
done

    cd ${BUILDDIR}/build

    if [ -L nls ] ; then
	rm nls
    fi

    ln -sf ${SRCDIR}/build/nls
}

check_args $@
clean_symlinks
create_symlinks

exit 0



