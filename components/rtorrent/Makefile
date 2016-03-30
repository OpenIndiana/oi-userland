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
# we really need to use studio, mostly because that's what
# sigc++ uses, so we don't like that parfait is clang/llvm in disguise
export PARFAIT_BUILD=no
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		rtorrent
COMPONENT_VERSION=	0.8.2
COMPONENT_PROJECT_URL=	http://libtorrent.rakshasa.no/
COMPONENT_ARCHIVE_HASH=	\
    sha256:76135a63869e43fa0392829bb45d94c0aa55e94350dddc272685ccfac1bbb2ed
COMPONENT_ARCHIVE_URL=	http://libtorrent.rakshasa.no/downloads/$(COMPONENT_ARCHIVE)

TPNO=			8824

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# requires an older automake to reconfigure
COMPONENT_PREP_ACTION = \
        (cd $(@D) ; \
	    aclocal-1.11 -I./scripts -I. ; \
	    autoheader; \
	    libtoolize --automake --copy --force; \
	    automake-1.11; \
	    autoconf )

# this is needed or we can't compile the rak headers
CC=$(CXX)

LDFLAGS += -L/usr/gnu/lib/$(MACH64) -R/usr/gnu/lib/$(MACH64)
ifeq ($(OS_VERSION),5.11)
LDFLAGS += -lnsl -lsocket
endif

CXXFLAGS +=	-i
CXXFLAGS +=	-template=no%extdef
CXXFLAGS +=	-I$(USRINCDIR)/ncurses
CONFIGURE_OPTIONS.64 +=         --srcdir=$(BUILD_DIR_64)
CONFIGURE_OPTIONS +=		--disable-debug

REQUIRED_PACKAGES += developer/build/automake-111
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/libtorrent
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
