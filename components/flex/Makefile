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
# Copyright 2016 Gary Mills
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

# Version 2.5.35 is no longer available.
COMPONENT_NAME=		flex
COMPONENT_VERSION=	2.5.36
COMPONENT_PROJECT_URL=	http://flex.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:c466e68bbbb0a7884301ba257376f98197254543799690b671b1ac2130645d55
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/flex/files/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/flex

SONAME=libfl.so.1
LDFLAGS = $(CC_BITS)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		M4="/usr/gnu/bin/m4"

COMPONENT_BUILD_ENV +=		SONAME="$(SONAME)"
COMPONENT_INSTALL_ENV +=	SONAME="$(SONAME)"

COMPONENT_TEST_ENV +=		PATH=/usr/gnu/bin:/usr/bin

COMPONENT_BUILD_TARGETS += $(SONAME)
COMPONENT_INSTALL_TARGETS += $(SONAME)

include ../../make-rules/shared-targets.mk

ASLR_MODE=$(ASLR_ENABLE)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64) 

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk

