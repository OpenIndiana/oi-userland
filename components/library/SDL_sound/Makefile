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

COMPONENT_NAME=		SDL_sound
COMPONENT_VERSION=	1.0.3
COMPONENT_PROJECT_URL=	http://icculus.org/SDL_sound/
COMPONENT_SUMMARY=	Sound decoding library for SDL
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:3999fd0bbb485289a52be14b2f68b571cb84e380cc43387eadf778f64c79e6df
COMPONENT_ARCHIVE_URL=	http://icculus.org/SDL_sound/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/audio/sdl-sound
COMPONENT_LICENSE =	LGPLv2
COMPONENT_LICENSE_FILE =	COPYING
COMPONENT_CLASSIFICATION =	System/Multimedia Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
# mpeg libraries are disabled for future 
# in case we ever have hipster-encumbered
CONFIGURE_OPTIONS +=	--disable-smpeg 
CONFIGURE_OPTIONS +=	--disable-mpglib
CONFIGURE_OPTIONS +=	--disable-mikmod
CONFIGURE_OPTIONS +=	--disable-modplug
CONFIGURE_OPTIONS +=	--disable-physfs


# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += codec/speex
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += system/library
