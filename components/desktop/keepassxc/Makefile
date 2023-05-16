#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
# Copyright 2019 Andreas Wacknitz <a.wacknitz@gmx.de>
# Copyright 2022 Carsten Grzemba
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		keepassxc
COMPONENT_VERSION=	2.7.5
COMPONENT_SUMMARY=	Cross-platform community-driven port of Keepass password manager
COMPONENT_PROJECT_URL=	https://keepassxc.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.xz
COMPONENT_ARCHIVE_HASH= sha256:ede24800901816c49569aa4f8bc7180a40cb8b554617fa2a2a2653caac13000c
COMPONENT_ARCHIVE_URL=  https://github.com/keepassxreboot/keepassxc/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		desktop/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_LICENSE=	GPL
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lsocket

CMAKE_OPTIONS += -DCMAKE_VERBOSE_MAKEFILE=ON
CMAKE_OPTIONS += -DKEEPASSXC_BUILD_TYPE=Release
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DWITH_XC_UPDATECHECK=OFF
CMAKE_OPTIONS += -DWITH_XC_BROWSER=ON
CMAKE_OPTIONS += -DWITH_XC_FDOSECRETS=ON
CMAKE_OPTIONS += -DWITH_XC_DOCS=off
CMAKE_OPTIONS += -DQt5_DIR=$(QT5_LIBDIR)/cmake/Qt5/
CMAKE_OPTIONS += -DCMAKE_INSTALL_RPATH=$(QT5_LIBDIR)
CMAKE_OPTIONS += -DCMAKE_LIBRARY_PATH=$(QT5_LIBDIR)

COMPONENT_TEST_TRANSFORMS+= '-e "s/[0-9. ]*sec//g"'

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/libqrencode
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/botan
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += security/argon2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxtst
