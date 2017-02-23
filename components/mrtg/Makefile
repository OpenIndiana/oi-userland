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

COMPONENT_NAME=		mrtg
COMPONENT_VERSION=	2.17.4
COMPONENT_PROJECT_URL=	http://oss.oetiker.ch/mrtg
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:5efa7fae8040159208472e5f889be5b41d8c8a2ea6b31616f0f75cc7f48d2365
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/pub/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	2023

TPNO=			25709

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS += -I$(BUILD_DIR_64)/bin
# Fix 64-bit linking via compiler.
LDFLAGS += $(CC_BITS)
CONFIGURE_OPTIONS += --with-gd-inc=$(USRINCDIR)/gd2

CONFIGURE_LIBDIR.64 = $(USRLIBDIR)

# Build process expects a bin directory in compilation area.
COMPONENT_PRE_BUILD_ACTION=(cd $(@D) ; mkdir -p bin)

REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += system/library/math
