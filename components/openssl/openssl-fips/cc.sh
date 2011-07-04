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
# Copyright (c) 2009, 2011, Oracle and/or its affiliates. All rights reserved.
#

# Very simple cc wrapper whose only purpose is to ensure that cc behaves as
# desired when linking the fipscanister.o object. Currently that means adding
# "-W2,-Rfully_unroll to the compiler options. As the fips module is only built
# with Sun Studio on sparc (gcc is used on x86) this workaround will only happen
# on sparc, in fact the compiler bug this is working around is sparc specific
# anyway.

exec $REALCC -W2,-Rfully_unroll "$@"
