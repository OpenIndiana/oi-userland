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

BUILD_STYLE=configure
BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         SDL2_mixer
COMPONENT_VERSION=      2.0.4
COMPONENT_PROJECT_URL=  https://www.libsdl.org/projects/SDL_mixer/
COMPONENT_SUMMARY=      SDL_mixer is a sample multi-channel audio mixer library
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:b4cf5a382c061cd75081cf246c2aa2f9df8db04bdda8dcdc6b6cca55bede2419
COMPONENT_ARCHIVE_URL=  https://www.libsdl.org/projects/SDL_mixer/release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/audio/sdl2-mixer
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE=      ZLIB
COMPONENT_LICENSE_FILE= COPYING.txt

ifeq ($(strip $(USE_ENCUMBERED)),yes)
COMPONENT_SUMMARY:=$(COMPONENT_SUMMARY) (encumbered version)
include $(WS_MAKE_RULES)/encumbered.mk
endif
TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=/usr/gnu/bin:/usr/gnu/bin/$(MACH64):/usr/bin/$(MACH64):/usr/bin

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
CONFIGURE_OPTIONS += --enable-music-mp3-mad-gpl

REQUIRED_PACKAGES += library/audio/libmad
else
CONFIGURE_OPTIONS +=	--disable-music-mp3
endif

REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
