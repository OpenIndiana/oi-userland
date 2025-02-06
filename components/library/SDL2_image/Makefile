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
# Copyright (c) 2024 Till Wegmueller
#

DROP_STATIC_LIBRARIES= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		SDL2_image
COMPONENT_VERSION=	2.8.4
COMPONENT_SUMMARY=	Simple DirectMedia Layer - Sample Image Loading Library
COMPONENT_PROJECT_URL=	https://libsdl.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:5a89a01420a192b89dbcc5f5267448181d5dcc81d2f5a1688cb1eac6f557da67
COMPONENT_ARCHIVE_URL=  https://github.com/libsdl-org/SDL_image/releases/download/release-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	image/library/sdl2-image
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE=	zlib
COMPONENT_LICENSE_FILE=	LICENSE.txt

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --disable-png-shared

# Auto-generated dependencies
REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += system/library
