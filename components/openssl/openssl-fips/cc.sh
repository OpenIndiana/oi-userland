#!/bin/sh
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
# Copyright (c) 2009, 2012, Oracle and/or its affiliates. All rights reserved.
#

# The fips module is built with Sun Studio cc compile on sparc and x86.
# On x86, this cc wrapper is used to remove "-fast" from the compiler
# option. According to the "OpenSSL FIPS 140-2 Security Policy"
# document, no file in the source distribution may be changed in any way
# and as a result, this wrapper is used to remove the -fast that is
# passed to the Studio cc compiler.
# On sparc, this wrapper is just a pass through to cc.

MACH=`uname -p`

if [ "$MACH" = "sparc" ]; then
	exec $REALCC "$@"
else
	CC_CMD=""
	while [ $# -ne 0 ]; do
        	if [ "$1" != "-fast" ]; then
                	CC_CMD="$CC_CMD '$1'"
        	fi
        	shift;
	done

	eval $REALCC $CC_CMD
fi

