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
USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         luanti
COMPONENT_VERSION=      5.16.1
COMPONENT_SUMMARY=      Multiplayer infinite-world block sandbox game
COMPONENT_PROJECT_URL=  https://www.luanti.org
COMPONENT_SRC=          luanti-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:57926752365a17d3bf64945ea04dc63cc446a8863037b043b97799af30126b6b
COMPONENT_ARCHIVE_URL=	https://github.com/luanti-org/luanti/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=         games/luanti
COMPONENT_CLASSIFICATION=	Applications/Games
COMPONENT_LICENSE=      Custom, CC BY-SA 3.0, CC BY-SA 4.0
COMPONENT_LICENSE_FILE=	LICENSE.txt

TEST_TARGET= $(NO_TESTS)
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
REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
