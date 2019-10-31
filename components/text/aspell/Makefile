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
# Copyright 2011 EveryCity Ltd. All rights reserved.
# Copyright 2019 Michal Nowak
#

BUILD_BITS=		32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		aspell
COMPONENT_VERSION=	0.60.8
COMPONENT_FMRI=		text/aspell
COMPONENT_SUMMARY=	GNU Aspell spell checking library
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:f9b77e515334a751b2e60daab5db23499e26c9209f5e7b7443b05235ad0226f2
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://aspell.net/	
COMPONENT_LICENSE=	LGPLv2.1

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CXXFLAGS+=-I/usr/include/ncurses

LDFLAGS.32=	$(LDFLAGS) -L$(GNULIB) -R $(GNULIB)
LDFLAGS.64=	$(LDFLAGS) -L$(GNULIB64) -R $(GNULIB64)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc 
CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static 
CONFIGURE_OPTIONS+=	--with-pic 
CONFIGURE_OPTIONS+=	--enable-curses="-lncurses"

CONFIGURE_OPTIONS.32+=	LDFLAGS="$(LDFLAGS.32)"
CONFIGURE_OPTIONS.64+=	LDFLAGS="$(LDFLAGS.64)"

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
