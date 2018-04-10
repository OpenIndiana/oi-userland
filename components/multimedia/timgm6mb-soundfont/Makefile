#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2018 Harry Liebel
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		timgm6mb-soundfont
COMPONENT_VERSION=	1.3
COMPONENT_FMRI=		multimedia/timgm6mb-soundfont
COMPONENT_PROJECT_URL=	https://musescore.org/en/handbook/soundfonts-and-sfz-files#gm_soundfonts
COMPONENT_SUMMARY=	Small MIDI SF2 SoundFont
COMPONENT_DESCRIPTION=	This is a small but complete General MIDI SoundFont originally packaged with MuseScore 1.3.
COMPONENT_CLASSIFICATION= Applications/Sound and Video
COMPONENT_SRC=		$(COMPONENT_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).orig.tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:af8f3a00e416dfb262bcaa904a1c84df04a51b72bbc1313aed012bc754bdf99b
COMPONENT_ARCHIVE_URL=	http://http.debian.net/debian/pool/main/t/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

PKG_OPTIONS += -D SF2_SHARE_DIR="/usr/share/sounds/sf2"

CLEAN_PATHS += $(BUILD_DIR)

# common targets
build:		prep

install:	build

clean::
	$(RM) -r $(CLEAN_PATHS)

# Auto-generated dependencies
