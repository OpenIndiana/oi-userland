#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2025 Niklas Poslovski
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         luanti
COMPONENT_VERSION=      5.11.0
COMPONENT_SUMMARY=      Multiplayer infinite-world block sandbox game
COMPONENT_PROJECT_URL=  https://www.luanti.org
COMPONENT_SRC=          luanti-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:70e531d0776988ce6e579ea5490fdf6be3e349a4ade5281f5111aa4fdd8ee510
COMPONENT_ARCHIVE_URL=	https://github.com/luanti-org/luanti/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=         games/luanti
COMPONENT_CLASSIFICATION=	Applications/Games
COMPONENT_LICENSE=      Custom, CC BY-SA 3.0, CC BY-SA 4.0
COMPONENT_LICENSE_FILE=	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

CXXFLAGS += -I/usr/include/ncurses
CMAKE_OPTIONS += -DRUN_IN_PLACE=FALSE

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += database/hiredis
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/audio/openal
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/jsoncpp
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libx11
