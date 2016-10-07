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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
COMPILER= gcc
export PARFAIT_BUILD=no

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		rtorrent
COMPONENT_VERSION=	0.9.6
COMPONENT_PROJECT_URL=	https://rakshasa.github.io/rtorrent/
COMPONENT_ARCHIVE_HASH=	\
    sha256:1e69c24f1f26f8f07d58d673480dc392bfc4317818c1115265b08a7813ff5b0e
COMPONENT_ARCHIVE_URL=	http://rtorrent.net/downloads/$(COMPONENT_ARCHIVE)

TPNO=			24573

TEST_TARGET= $(NO_TESTS)

# Needs updated sigcpp, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CXXFLAGS += -std=c++11

LDFLAGS += -L$(GNULIB64) -R$(GNULIB64)
ifeq ($(OS_VERSION),5.11)
LDFLAGS += -lnsl -lsocket
endif

CXXFLAGS +=		-I$(USRINCDIR)/ncurses
CONFIGURE_OPTIONS.64 +=	--srcdir=$(BUILD_DIR_64)
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--disable-debug

REQUIRED_PACKAGES += developer/build/automake-115
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/libtorrent
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
