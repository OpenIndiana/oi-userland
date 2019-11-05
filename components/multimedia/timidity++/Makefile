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
# Copyright 2018 Harry Liebel <hliebel@gmail.com>
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		timidity++
COMPONENT_VERSION=	2.14.0
COMPONENT_FMRI=		multimedia/timidity++
COMPONENT_PROJECT_URL=	https://sourceforge.net/projects/timidity
COMPONENT_SUMMARY=	Software MIDI player
COMPONENT_DESCRIPTION=	A software synthesizer, without external instruments, that can play MIDI files without a hardware synthesizer. It can either render to the sound card in real time, or it can save the result to a file, such as a PCM .wav file.
COMPONENT_CLASSIFICATION= Applications/Sound and Video
COMPONENT_SRC=		TiMidity++-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
  sha256:f97fb643f049e9c2e5ef5b034ea9eeb582f0175dce37bc5df843cc85090f6476
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/files/TiMidity++/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	timidity++.license
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --enable-audio=oss,ao,vorbis,flac
CONFIGURE_OPTIONS += --enable-ncurses

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += library/audio/libao
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/header/header-audio
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
