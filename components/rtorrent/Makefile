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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		rtorrent
COMPONENT_VERSION=	0.9.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://rakshasa.github.io/rtorrent/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:bc0a2c1ee613b68f37021beaf4e64a9252f91ed06f998c1e897897c354ce7e84
COMPONENT_ARCHIVE_URL=	http://rtorrent.net/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/rtorrent

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

LDFLAGS    += -lnsl -lsocket

CXXFLAGS +=     $(gcc_OPT)
LDFLAGS.32 += -L/usr/gnu/lib -R/usr/gnu/lib
LDFLAGS.64 += -L/usr/gnu/lib/$(MACH64) -R/usr/gnu/lib/$(MACH64)
LDFLAGS += $(LDFLAGS.$(BITS))
CXXFLAGS +=	-I/usr/include/ncurses
CONFIGURE_OPTIONS.32 +=		--srcdir=$(BUILD_DIR_32)
CONFIGURE_OPTIONS.64 +=		--srcdir=$(BUILD_DIR_64)
CONFIGURE_OPTIONS +=		--disable-debug

PKG_PROTO_DIRS += $(BUILD_DIR)/$(MACH32)/doc

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

