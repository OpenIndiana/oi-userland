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
# Copyright (c) 2012, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libedit
COMPONENT_VERSION=	20150325-3.1
IPS_COMPONENT_VERSION=  3.1
COMPONENT_PROJECT_URL=	http://www.thrysoee.dk/editline/
COMPONENT_ARCHIVE_HASH=	\
    sha256:c88a5e4af83c5f40dda8455886ac98923a9c33125699742603a88a0253fcc8c5
COMPONENT_ARCHIVE_URL=	http://www.thrysoee.dk/editline/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libedit
COMPONENT_ANITYA_ID=	1599

TPNO=			22295

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=   --enable-shared
CONFIGURE_OPTIONS +=   --disable-static
