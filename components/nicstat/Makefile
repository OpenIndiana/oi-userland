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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		nicstat
COMPONENT_VERSION=	1.95
COMPONENT_PROJECT_URL=	http://sourceforge.net/projects/nicstat/
COMPONENT_ARCHIVE_HASH=	\
    sha256:c4cc33f8838f4523f27c3d7584eedbe59f4c587f0821612f5ac2201adc18b367
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)files/$(COMPONENT_ARCHIVE)/download
COMPONENT_ANITYA_ID=	10373

TPNO=			20669

BUILD_STYLE= justmake
# Makefile.Solaris is pretty useless for working in Userland.
INSTALL_TARGET= build
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ARGS += COPT="$(CFLAGS)"
COMPONENT_BUILD_ARGS +=	-f Makefile.Solaris

PATCH_LEVEL =		0

# Just get stuff from the build directory.
PKG_PROTO_DIRS += $(BUILD_DIR_64)
