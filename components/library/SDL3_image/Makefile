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
# Copyright (c) 2025 Andreas Wacknitz
#

BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		SDL3_image
COMPONENT_VERSION=	3.4.4
COMPONENT_SUMMARY=	Simple DirectMedia Layer - Sample Image Loading Library
COMPONENT_PROJECT_URL=	https://libsdl.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:29751304a13d25ac513f24305fa25b06a6edd9607718c90129b8350d35fc5573
COMPONENT_ARCHIVE_URL=  https://github.com/libsdl-org/SDL_image/releases/download/release-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	image/library/sdl3-image
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE=	zlib
COMPONENT_LICENSE_FILE=	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DSDLIMAGE_TESTS=ON
# avif support is only available in encumbered, so don't run tests for it
CMAKE_OPTIONS += -DSDLIMAGE_AVIF=OFF

PATH= $(PATH.gnu)

# Manually added build dependencies
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/libwebp

# Auto-generated dependencies
REQUIRED_PACKAGES += library/sdl3
REQUIRED_PACKAGES += system/library
