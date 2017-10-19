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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	ncurses
COMPONENT_VERSION=	6.0-20171014
IPS_COMPONENT_VERSION=	$(subst -,.,$(COMPONENT_VERSION))
COMPONENT_SUMMARY=	A CRT screen handling and optimization package.
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/ncurses/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
    sha256:6bd5b15a0d64f65a2a84c60e7bebb8467cfd7312b886309c5ecd87ea5c441ace
COMPONENT_ARCHIVE_URL=	http://invisible-mirror.net/archives/ncurses/current/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/ncurses
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Needed to make "gmake test" work.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_PREFIX =	/usr/gnu

# force XPG6 standard
CXXFLAGS += -D_XPG6
LDFLAGS += -D_XPG6
CPPFLAGS += -D_XPG6
CFLAGS += -std=c99 -D_POSIX_C_SOURCE=200112L

CONFIGURE_OPTIONS +=	--with-shared
CONFIGURE_OPTIONS +=	--with-normal
CONFIGURE_OPTIONS +=	--with-abi-version=5
CONFIGURE_OPTIONS +=	--enable-rpath
CONFIGURE_OPTIONS +=	--enable-widec
CONFIGURE_OPTIONS +=	--enable-symlinks
CONFIGURE_OPTIONS +=	--disable-lib-suffixes
CONFIGURE_OPTIONS +=	--includedir=$(USRINCDIR)/ncurses
CONFIGURE_OPTIONS +=	--with-pkg-config-libdir=$(PKG_CONFIG_PATH)
CONFIGURE_OPTIONS +=	--enable-pc-files

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

COMPONENT_TEST_DIR =		$(BUILD_DIR)/$(MACH$(BITS))/test
COMPONENT_TEST_TARGETS =

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(NO_TESTS)

REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
