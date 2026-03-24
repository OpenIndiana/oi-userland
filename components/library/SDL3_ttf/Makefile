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
# Copyright 2025 Marcel Telka
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			SDL3_ttf
COMPONENT_VERSION=		3.2.2
COMPONENT_SUMMARY=		Support for TrueType (.ttf) font files with Simple Directmedia Layer
COMPONENT_PROJECT_URL=		https://github.com/libsdl-org/SDL_ttf
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=		sha256:63547d58d0185c833213885b635a2c0548201cc8f301e6587c0be1a67e1e045d
COMPONENT_ARCHIVE_URL=		$(COMPONENT_PROJECT_URL)/releases/download/release-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			image/library/sdl3-ttf
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE=		Zlib
COMPONENT_LICENSE_FILE=		LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/sdl3
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
