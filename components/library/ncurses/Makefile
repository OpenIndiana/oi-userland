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
# Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2013  Erol Zavidic. All rights reserverd.
# Copyright (c) 2016  Adam Stevko. All rights reserverd.
# Copyright (c) 2019  Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ncurses
COMPONENT_VERSION=	6.1
COMPONENT_REV=		20190713
IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).$(COMPONENT_REV)
COMPONENT_SUMMARY=	A CRT screen handling and optimization package.
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/ncurses/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-$(COMPONENT_REV)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
	sha256:115a8a926825db70a52d397e8d94c01064941e81a6c50016934e2c604e36a9c3
COMPONENT_ARCHIVE_URL=	https://invisible-mirror.net/archives/$(COMPONENT_NAME)/current/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_FMRI=		library/ncurses
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Needed for the 'test' target to work
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_PREFIX =	/usr/gnu

# force XPG6 standard
CXXFLAGS += -D_XPG6
LDFLAGS += -D_XPG6
CPPFLAGS += -D_XPG6
CFLAGS += -std=c99 -D_POSIX_C_SOURCE=200112L

CONFIGURE_OPTIONS +=	--enable-rpath
# From INSTALL file:
# NOTE: applications compiled with this configuration are not compatible
# with those built for 8-bit characters.  You cannot simply make a
# symbolic link to equate libncurses.so with libncursesw.so.
CONFIGURE_OPTIONS +=	--enable-widec
CONFIGURE_OPTIONS +=	--enable-symlinks
CONFIGURE_OPTIONS +=	--enable-pc-files
CONFIGURE_OPTIONS +=	--disable-lib-suffixes
CONFIGURE_OPTIONS +=	--with-pkg-config-libdir=$(PKG_CONFIG_PATH.$(BITS))
CONFIGURE_OPTIONS +=	--with-pcre2
CONFIGURE_OPTIONS +=	--with-shared
# Compatibility with older programs
CONFIGURE_OPTIONS +=	--with-abi-version=5
CONFIGURE_OPTIONS +=	--with-normal
CONFIGURE_OPTIONS +=	--without-debug
CONFIGURE_OPTIONS +=	--includedir=$(USRINCDIR)/ncurses

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# We need ncurses.so in /usr/lib
COMPONENT_POST_INSTALL_ACTION += \
	$(MV) $(PROTO_DIR)$(CONFIGURE_PREFIX)/lib/libncurses.so* $(PROTO_DIR)/usr/lib/ || \
	$(MV) $(PROTO_DIR)$(CONFIGURE_PREFIX)/lib/amd64/libncurses.so* $(PROTO_DIR)/usr/lib/amd64/ ;

COMPONENT_TEST_DIR =		$(BUILD_DIR)/$(MACH$(BITS))/test
COMPONENT_TEST_TARGETS =

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
