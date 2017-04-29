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
# Copyright (c) 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		SDL_image
COMPONENT_VERSION=	1.2.12
COMPONENT_PROJECT_URL=	http://www.libsdl.org/projects/SDL_image/
COMPONENT_SUMMARY=	Simple DirectMedia Layer - Sample Image Loading Library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0b90722984561004de84847744d566809dbb9daf732a9e503b91a1b5a84e5699
COMPONENT_ARCHIVE_URL=	http://www.libsdl.org/projects/SDL_image/release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	image/library/sdl-image
COMPONENT_LICENSE =	zlib
COMPONENT_LICENSE_FILE =	COPYING
COMPONENT_CLASSIFICATION =	System/Multimedia Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS +=	--disable-png-shared

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += system/library
