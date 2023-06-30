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
# Copyright 2018 Harry Liebel <hliebel@gmail.com>
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		chromium-bsu
COMPONENT_VERSION=	0.9.16.1
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Arcade-style, top-scrolling space shooter
COMPONENT_DESCRIPTION=	Chromium B.S.U. is a fast paced, arcade-style, top-scrolling shooter. It uses OpenGL for graphics, and OpenAL for sound effects.
COMPONENT_PROJECT_URL=	https://sourceforge.net/projects/chromium-bsu
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:a1c141a34d19a59607ae81166a19864eb8c84cf86b155462fed31a6d56e1624a
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)/files/Chromium%20B.S.U.%20source%20code/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		games/chromium-bsu
COMPONENT_CLASSIFICATION= Applications/Games
COMPONENT_LICENSE=	Artistic
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --enable-nls
CONFIGURE_OPTIONS += --enable-ftgl
CONFIGURE_OPTIONS += --enable-glut
CONFIGURE_OPTIONS += --enable-openal
CONFIGURE_OPTIONS += --enable-sdl
CONFIGURE_OPTIONS += --enable-sdlimage
CONFIGURE_OPTIONS += --disable-sdlmixer
CONFIGURE_OPTIONS += --disable-sdl2
CONFIGURE_OPTIONS += --disable-sdl2mixer
CONFIGURE_OPTIONS += --disable-sdl2image
CONFIGURE_OPTIONS += --disable-glc
CONFIGURE_OPTIONS += --disable-glpng 
CONFIGURE_OPTIONS += --disable-rpath

# Build dependencies
REQUIRED_PACKAGES += text/gnu-gettext

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/sdl-image
REQUIRED_PACKAGES += library/audio/freealut
REQUIRED_PACKAGES += library/audio/openal
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += library/x11/ftgl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/glu
