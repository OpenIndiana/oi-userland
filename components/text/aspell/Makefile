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
# Copyright 2022 Andreas Wacknitz
#

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		aspell
COMPONENT_VERSION=	0.60.8.1
COMPONENT_SUMMARY=	GNU Aspell spell checking library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:d6da12b34d42d457fa604e435ad484a74b2effcd120ff40acd6bb3fb2887d21b
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://aspell.net/	
COMPONENT_FMRI=		text/aspell
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CXXFLAGS += -I/usr/include/ncurses

LDFLAGS.64=	$(LDFLAGS) -L$(GNULIB64) -R$(GNULIB64)

CONFIGURE_OPTIONS += --sysconfdir=/etc 
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static 
CONFIGURE_OPTIONS += --with-pic 
CONFIGURE_OPTIONS += --enable-curses="-lncurses"

CONFIGURE_OPTIONS.64 += LDFLAGS="$(LDFLAGS.64)"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
