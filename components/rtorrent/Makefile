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

# we really need to use studio, mostly because that's what
# sigc++ uses, so we don't like that parfait is g++ in disguise
PARFAIT_BUILD=no

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		rtorrent
COMPONENT_VERSION=	0.8.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://libtorrent.rakshasa.no/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:76135a63869e43fa0392829bb45d94c0aa55e94350dddc272685ccfac1bbb2ed
COMPONENT_ARCHIVE_URL=	http://libtorrent.rakshasa.no/downloads/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PREP_ACTION = \
        (cd $(@D) ; \
	    aclocal -I./scripts -I. ; \
	    autoheader; \
	    libtoolize --automake --copy --force; \
	    automake; \
	    autoconf )

# this is needed or we can't compile the rak headers
CC=$(CXX)

LDFLAGS += -L/usr/gnu/lib -R/usr/gnu/lib -lnsl -lsocket

CXXFLAGS +=	-i
CXXFLAGS +=	-xspace
CXXFLAGS +=	$(studio_XREGS)
CXXFLAGS +=	-I/usr/include/ncurses
CONFIGURE_OPTIONS.32 +=		--srcdir=$(BUILD_DIR_32)
CONFIGURE_OPTIONS +=		--disable-debug
CONFIGURE_OPTIONS +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=		LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS +=		CXXFLAGS="$(CXXFLAGS)"


# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
