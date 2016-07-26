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
# Copyright (c) 2016 Jim Klimov
#

# NOTE: This recipe supports both "encumbered" and "license-clean"
# builds (with or without MP3 support).
# A not-encumbered Makefile which includes this one could be delivered
# as $(WS_TOP)/library/SDL2_mixer/Makefile in some other reality.
# That file's contents would be just two lines like these:
### USE_ENCUMBERED=no
### include ../../encumbered/SDL2_mixer/Makefile
# Also the other version of the component should deliver a symlink to
# the P5M manifest.

# This file (by default) provides the package with encumbered code
# or inseparable run-time dependencies:
USE_ENCUMBERED?=yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		SDL2_mixer
COMPONENT_VERSION=	2.0.1
COMPONENT_PROJECT_URL=	http://www.libsdl.org/projects/SDL_mixer/
COMPONENT_SUMMARY=	SDL_mixer is a sample multi-channel audio mixer library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:5a24f62a610249d744cbd8d28ee399d8905db7222bf3bdbc8a8b4a76e597695f
COMPONENT_ARCHIVE_URL=	http://www.libsdl.org/projects/SDL_mixer/release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/audio/sdl2-mixer
COMPONENT_LICENSE =	ZLIB
COMPONENT_LICENSE_FILE =	COPYING.txt
COMPONENT_CLASSIFICATION =	System/Multimedia Libraries

ifeq ($(strip $(USE_ENCUMBERED)),yes)
COMPONENT_SUMMARY:=$(COMPONENT_SUMMARY) (encumbered version)
include $(WS_MAKE_RULES)/encumbered.mk
endif
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH.32=/usr/gnu/bin:/usr/bin
PATH.64=/usr/gnu/bin:/usr/gnu/bin/$(MACH64):/usr/bin/$(MACH64):/usr/bin
PATH=$(PATH.$(BITS))

COMPONENT_PREP_ACTION = ( cd $(@D) && ./autogen.sh )

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS +=	--enable-music-cmd
CONFIGURE_OPTIONS +=	--enable-music-wave
CONFIGURE_OPTIONS +=	--enable-music-midi
CONFIGURE_OPTIONS +=	--enable-music-mod-mikmod --enable-music-mod-mikmod-shared
CONFIGURE_OPTIONS +=	--enable-music-ogg-shared
CONFIGURE_OPTIONS +=	--enable-music-flac-shared

ifeq ($(strip $(USE_ENCUMBERED)),yes)
### Note: currently we do not serve libmad in the fully open components,
### it and MPEG support is reserved for encumbered components
#CONFIGURE_OPTIONS +=	--enable-music-mp3-smpeg --enable-music-mp3-smpeg-shared
CONFIGURE_OPTIONS +=	--enable-music-mp3-mad-gpl
REQUIRED_PACKAGES += library/audio/libmad
else
CONFIGURE_OPTIONS +=	--disable-music-mp3
endif

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
