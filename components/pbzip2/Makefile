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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		pbzip2
COMPONENT_VERSION=	1.1.13
COMPONENT_PROJECT_URL=	http://compression.ca/pbzip2/
COMPONENT_ARCHIVE_HASH=	\
    sha256:8fd13eaaa266f7ee91f85c1ea97c86d9c9cc985969db9059cdebcb1e1b7bdbe6
COMPONENT_ARCHIVE_URL=	https://launchpad.net/pbzip2/1.1/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	2602

TPNO=			27242

BUILD_STYLE= justmake
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CXX += -std=sun03

# pbzip2 Solaris Sun Studio build uses a non-standard Makefile
COMPONENT_BUILD_ARGS +=		CC="$(CXX)"
COMPONENT_BUILD_ARGS +=		-f Makefile.solaris.sunstudio
COMPONENT_INSTALL_ARGS +=	-f Makefile.solaris.sunstudio
COMPONENT_INSTALL_ARGS +=	PREFIX=$(PROTOUSRDIR)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/math
