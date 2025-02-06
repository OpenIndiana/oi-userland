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
# Copyright (c) 2020  Michal Nowak
#

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ncurses
COMPONENT_VERSION=	6.5
COMPONENT_SUMMARY=	A CRT screen handling and optimization package.
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/ncurses/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:136d91bc269a9a5785e5f9e980bc76ab57428f604ce3e5a5a90cebc767971cc6
COMPONENT_ARCHIVE_URL=	https://invisible-mirror.net/archives/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_FMRI=		library/ncurses
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

#TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Needed for the 'test' target to work
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_PREFIX= /usr/gnu

# force XPG6 standard
CXXFLAGS += -D_XPG6
LDFLAGS += -D_XPG6
CPPFLAGS += -D_XPG6
CFLAGS += -std=c99 -D_POSIX_C_SOURCE=200112L

CONFIGURE_OPTIONS += --enable-rpath
# From INSTALL file:
# NOTE: applications compiled with this configuration are not compatible
# with those built for 8-bit characters.  You cannot simply make a
# symbolic link to equate libncurses.so with libncursesw.so.
CONFIGURE_OPTIONS += --enable-widec
CONFIGURE_OPTIONS += --enable-symlinks
CONFIGURE_OPTIONS += --enable-pc-files
CONFIGURE_OPTIONS += --disable-lib-suffixes
CONFIGURE_OPTIONS += --with-pkg-config-libdir=$(PKG_CONFIG_PATH.$(BITS))
CONFIGURE_OPTIONS += --with-pcre2
CONFIGURE_OPTIONS += --with-shared
# Compatibility with older programs
CONFIGURE_OPTIONS += --with-abi-version=5
# Disable static libraries
CONFIGURE_OPTIONS += --without-normal
CONFIGURE_OPTIONS += --without-debug
CONFIGURE_OPTIONS += --includedir=$(USRINCDIR)/ncurses

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# We need ncurses.so in /usr/lib
COMPONENT_POST_INSTALL_ACTION += \
	$(MV) $(PROTO_DIR)$(CONFIGURE_PREFIX)/lib/libncurses.so* $(PROTO_DIR)/usr/lib/ || \
	$(MV) $(PROTO_DIR)$(CONFIGURE_PREFIX)/lib/$(MACH64)/libncurses.so* $(PROTO_DIR)/usr/lib/$(MACH64)/ ;

# The provided test programs are interactive, so they won't be usable for our machinery.
COMPONENT_TEST_DIR= $(BUILD_DIR)/$(MACH$(BITS))/test
COMPONENT_TEST_TARGETS= check
COMPONENT_PRE_TEST_ACTION= ( cd $(COMPONENT_TEST_DIR) && PATH="$(PATH)" ./configure )

# Auto-generated dependencies
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
