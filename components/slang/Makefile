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

COMPONENT_NAME=		slang
COMPONENT_VERSION=	2.2.4
IPS_PKG_NAME=		library/slang
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha1:34e68a993888d0ae2ebc7bc31b40bc894813a7e2
COMPONENT_ARCHIVE_URL=	ftp://space.mit.edu/pub/davis/slang/v2.2/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.jedsoft.org/slang/
COPYRIGHT_FILE=		slang.license
COPYRIGHTS=		GPLv2

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PKG_MACROS +=	IPS_PKG_NAME=$(IPS_PKG_NAME)
PKG_MACROS +=	COPYRIGHT_FILE=$(COPYRIGHT_FILE)
PKG_MACROS +=	COPYRIGHTS=$(COPYRIGHTS)

COMPONENT_PRE_CONFIGURE_ACTION = $(CLONEY) $(SOURCE_DIR) $(@D)
CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=		LDFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=		--sysconfdir=$(ETCDIR)/slsh

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
