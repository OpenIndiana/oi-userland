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

BUILD_STYLE=justmake
USE_PARALLEL_BUILD=yes
include ../../../make-rules/shared-macros.mk

# The last release is 1.51c (2019); upstream's builds are from master.
COMPONENT_GIT_HASH=	438e7d413b5f7277187c35b032eb0ef9093ae778

COMPONENT_NAME=		iortcw
COMPONENT_VERSION=	1.51.20240526
COMPONENT_SUMMARY=	Return to Castle Wolfenstein engines, SP and MP (game data not included)
COMPONENT_PROJECT_URL=	https://github.com/iortcw/iortcw
COMPONENT_FMRI=		games/iortcw
COMPONENT_CLASSIFICATION=Applications/Games
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_GIT_HASH)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/iortcw/iortcw/archive/$(COMPONENT_GIT_HASH).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:e13b6e777f60163b2e0dbfd23be23606f7f3b933dcf0440b67d6457d7dc4d024
COMPONENT_LICENSE=	GPLv3 with additional terms
COMPONENT_LICENSE_FILE=	SP/COPYING.txt

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# SP/ (single player) and MP/ (multiplayer and its dedicated server) are
# two trees with a Makefile each; both install into /usr/lib/iortcw.
# /usr/bin/iortcw-* are links (see the manifest), so the engines must not
# take their base directory from argv[0].
RTCW_LIBDIR=		$(USRLIBDIR)/iortcw
# The system's libraries; the Opus codec needs opusfile, which is not
# packaged, VoIP needs only libopus (02-voip-without-opusfile.patch).
RTCW_ARGS=		USE_INTERNAL_LIBS=0 USE_LOCAL_HEADERS=0
RTCW_ARGS+=		USE_CODEC_OPUS=0 USE_CURL=1 USE_FREETYPE=1 USE_XDG=1
RTCW_ARGS+=		DEFAULT_BASEDIR=$(RTCW_LIBDIR)
RTCW_ARGS+=		CC="$(CC)" CXX="$(CXX)" NO_STRIP=1 V=1

COMPONENT_BUILD_ACTION= \
	for d in SP MP; do \
		$(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) -C $(@D)/$$d \
		    $(COMPONENT_BUILD_GMAKE_ARGS) $(RTCW_ARGS) release || exit 1; \
	done

COMPONENT_INSTALL_ACTION= \
	$(INSTALL) -d $(PROTO_DIR)$(RTCW_LIBDIR); \
	for d in SP MP; do \
		$(ENV) $(COMPONENT_INSTALL_ENV) $(GMAKE) -C $(@D)/$$d \
		    $(RTCW_ARGS) COPYDIR=$(PROTO_DIR)$(RTCW_LIBDIR) \
		    copyfiles || exit 1; \
	done
# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
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
