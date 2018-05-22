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
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		aspell
COMPONENT_VERSION=	0.60.6.1
COMPONENT_REVISION=	2
COMPONENT_FMRI=		text/aspell
COMPONENT_SUMMARY=	GNU Aspell spell checking library
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:f52583a83a63633701c5f71db3dc40aab87b7f76b29723aeb27941eff42df6e1
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://aspell.net/	
COMPONENT_LICENSE=	LGPLv2.1


include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CXXFLAGS+=-I/usr/include/ncurses

LDFLAGS.32=	$(LDFLAGS) -L$(GNULIB) -R $(GNULIB)
LDFLAGS.64=	$(LDFLAGS) -L$(GNULIB64) -R $(GNULIB64)

COMPONENT_PRE_CONFIGURE_ACTION += cp -r $(SOURCE_DIR)/* $(@D) && \
			cd $(@D) && autoconf
CONFIGURE_OPTIONS+=	--sysconfdir=/etc 
CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static 
CONFIGURE_OPTIONS+=	--with-pic 
CONFIGURE_OPTIONS+=	--with-curses=ncurses 

CONFIGURE_OPTIONS.32+=	LDFLAGS="$(LDFLAGS.32)"
CONFIGURE_OPTIONS.64+=	LDFLAGS="$(LDFLAGS.64)"

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
