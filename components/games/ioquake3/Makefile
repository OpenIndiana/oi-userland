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
# Copyright 2026 Ignacio Soriano
#

BUILD_STYLE=cmake
USE_PARALLEL_BUILD=yes
include ../../../make-rules/shared-macros.mk

# No release since 1.36 (2009); upstream's builds are from master.
COMPONENT_GIT_HASH=	87a99d18206e878a20289f05ac3c16005dcae5c3

COMPONENT_NAME=		ioquake3
COMPONENT_VERSION=	1.36.20261012
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Quake III Arena engine (game data not included)
COMPONENT_PROJECT_URL=	https://ioquake3.org/
COMPONENT_FMRI=		games/ioquake3
COMPONENT_CLASSIFICATION=Applications/Games
COMPONENT_SRC=		ioq3-$(COMPONENT_GIT_HASH)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/ioquake/ioq3/archive/$(COMPONENT_GIT_HASH).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:8c0c2cdc2326a5f303afe09914b445609780f1ff9337fab5224afc33607bf720
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING.txt

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# The engine, its renderers and game modules in one directory, as upstream
# installs them; /usr/bin/ioquake3 is a link (see the manifest), so the
# engine must not take its base directory from argv[0].
CMAKE_PREFIX=		$(USRLIBDIR)/ioquake3
CFLAGS+=		-DDEFAULT_BASEDIR=\\\"$(CMAKE_PREFIX)\\\"

# The system's libraries, not the copies in code/thirdparty.
CMAKE_OPTIONS+=		-DUSE_INTERNAL_LIBS=OFF
CMAKE_OPTIONS+=		-DSDL2_DIR=$(USRLIBDIR64)/cmake/SDL2
# The Opus codec needs opusfile, which is not packaged; VoIP needs only
# libopus (02-voip-without-opusfile.patch).
CMAKE_OPTIONS+=		-DUSE_CODEC_OPUS=OFF
CMAKE_OPTIONS+=		-DUSE_FREETYPE=ON

# Upstream has AppStream metadata naming ioquake3.desktop and the icons,
# but no desktop entry (files/ioquake3.desktop).
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -d $(PROTO_DIR)$(USRSHAREDIR)/applications \
		$(PROTO_DIR)$(USRSHAREDIR)/metainfo \
		$(PROTO_DIR)$(USRSHAREDIR)/icons/hicolor/scalable/apps \
		$(PROTO_DIR)$(USRSHAREDIR)/icons/hicolor/256x256/apps \
		$(PROTO_DIR)$(USRSHAREDIR)/icons/hicolor/32x32/apps; \
	$(INSTALL) -m 0444 $(COMPONENT_DIR)/files/ioquake3.desktop \
		$(PROTO_DIR)$(USRSHAREDIR)/applications/ioquake3.desktop; \
	$(INSTALL) -m 0444 $(SOURCE_DIR)/misc/linux/org.ioquake3.ioquake3.metainfo.xml \
		$(PROTO_DIR)$(USRSHAREDIR)/metainfo/org.ioquake3.ioquake3.metainfo.xml; \
	$(INSTALL) -m 0444 $(SOURCE_DIR)/misc/quake3.svg \
		$(PROTO_DIR)$(USRSHAREDIR)/icons/hicolor/scalable/apps/ioquake3.svg; \
	$(INSTALL) -m 0444 $(SOURCE_DIR)/misc/linux/quake3-tango.png \
		$(PROTO_DIR)$(USRSHAREDIR)/icons/hicolor/256x256/apps/ioquake3.png; \
	$(INSTALL) -m 0444 $(SOURCE_DIR)/misc/quake3.png \
		$(PROTO_DIR)$(USRSHAREDIR)/icons/hicolor/32x32/apps/ioquake3.png

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += library/audio/openal
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/opus
REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
