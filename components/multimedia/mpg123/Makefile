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
# Copyright 2019 Alexander Pyhalov
#

BUILD_BITS= 32_and_64
PREFERRED_BITS = 64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= mpg123
COMPONENT_VERSION= 1.25.12
COMPONENT_SUMMARY= Fast console MPEG Audio Player and decoder library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:1ffec7c9683dfb86ea9040d6a53d6ea819ecdda215df347f79def08f1fe731d1
COMPONENT_ARCHIVE_URL= \
  http://mpg123.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL= $(COMPONENT_ARCHIVE_URL).sig
COMPONENT_PROJECT_URL = http://mpg123.org/
COMPONENT_FMRI = audio/mpg123
COMPONENT_CLASSIFICATION = Applications/Sound and Video
COMPONENT_LICENSE = LGPLv2,GPLv2
COMPONENT_LICENSE_FILE = COPYING

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CFLAGS += -D__EXTENSIONS__

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-int-quality
CONFIGURE_OPTIONS += --enable-fifo
CONFIGURE_OPTIONS += --enable-network
CONFIGURE_OPTIONS += --enable-ipv6=yes
CONFIGURE_OPTIONS += --with-optimization=3
CONFIGURE_OPTIONS.32 += --with-cpu=sse
CONFIGURE_OPTIONS.64 += --with-cpu=x86-64
CONFIGURE_OPTIONS += --with-default-audio=pulse

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/openal
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
