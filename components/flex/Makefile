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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		flex
COMPONENT_VERSION=	2.5.35
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha1:c507095833aaeef2d6502e12638e54bf7ad2f24a
COMPONENT_ARCHIVE_URL=	http://softlayer.dl.sourceforge.net/project/flex/flex/flex-2.5.35/flex-2.5.35.tar.bz2

SONAME=libfl.so.1
LDFLAGS = $(CC_BITS)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=		CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS  +=		LDFLAGS="$(LDFLAGS)"

COMPONENT_BUILD_ENV +=		SONAME="$(SONAME)"
COMPONENT_INSTALL_ENV +=	SONAME="$(SONAME)"

COMPONENT_TEST_ENV +=		PATH=/usr/gnu/bin:/usr/bin

COMPONENT_BUILD_TARGETS += $(SONAME)
COMPONENT_INSTALL_TARGETS += $(SONAME)

include ../../make-rules/shared-targets.mk

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64) 

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk

