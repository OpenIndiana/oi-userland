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

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		timidity++
COMPONENT_VERSION=	2.15.0
COMPONENT_REVISION= 1
COMPONENT_SUMMARY=	Software MIDI player
COMPONENT_DESCRIPTION=	A software synthesizer, without external instruments, that can play MIDI files without a hardware synthesizer. It can either render to the sound card in real time, or it can save the result to a file, such as a PCM .wav file.
COMPONENT_PROJECT_URL=	https://sourceforge.net/projects/timidity
COMPONENT_SRC=		TiMidity++-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:161fc0395af16b51f7117ad007c3e434c825a308fa29ad44b626ee8f9bb1c8f5
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/files/TiMidity++/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		multimedia/timidity++
COMPONENT_CLASSIFICATION= Applications/Sound and Video
COMPONENT_LICENSE_FILE=	timidity++.license
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --enable-audio=oss,ao,vorbis,flac
CONFIGURE_OPTIONS += --enable-ncurses

# Manually added build dependencies
REQUIRED_PACKAGES += system/header/header-audio

# Auto-generated dependencies
REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += library/audio/libao
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
