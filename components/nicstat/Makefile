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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		nicstat
COMPONENT_VERSION=	1.95
COMPONENT_PROJECT_URL=	http://sourceforge.net/projects/nicstat/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c4cc33f8838f4523f27c3d7584eedbe59f4c587f0821612f5ac2201adc18b367
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)files/$(COMPONENT_ARCHIVE)/download
COMPONENT_BUGDB=	utility/nicstat

TPNO=			20669

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV +=	CC="$(CC) -m64"
COMPONENT_BUILD_ARGS =	-f Makefile.Solaris

PATCH_LEVEL =		0

# Just get stuff from the build directory.
PKG_PROTO_DIRS += $(BUILD_DIR_64)

ASLR_MODE = $(ASLR_ENABLE)

build:		$(BUILD_64)

# Makefile.Solaris is pretty useless for working in Userland.
install:	$(BUILD_64)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)

REQUIRED_PACKAGES += system/library
