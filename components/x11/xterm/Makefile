#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Alexander Pyhalov
# Copyright 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xterm
COMPONENT_VERSION=	348
COMPONENT_SUMMARY=	Xterm - terminal emulator for X 
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
	sha256:8b1f5121dbf3690de9d85a3b9329e3357021705dd7c21da192e47542769275be
COMPONENT_ARCHIVE_URL= \
	http://invisible-mirror.net/archives/xterm/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://invisible-island.net/xterm/
COMPONENT_FMRI=		terminal/xterm
COMPONENT_LICENSE=	MIT
COMPONENT_CLASSIFICATION=Applications/System Utilities

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS += --enable-256-color
CONFIGURE_OPTIONS += --enable-88-color
CONFIGURE_OPTIONS += --enable-wide-chars
CONFIGURE_OPTIONS += --disable-setuid
CONFIGURE_OPTIONS += --disable-setgid
CONFIGURE_OPTIONS += --enable-luit
CONFIGURE_OPTIONS += --disable-imake
CONFIGURE_OPTIONS += --with-app-defaults=/usr/share/X11/app-defaults
CONFIGURE_OPTIONS += --with-icondir=/usr/share/pixmaps
CONFIGURE_OPTIONS += --enable-logging

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += terminal/luit

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/libxpm
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
