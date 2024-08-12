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
# Copyright 2021,2024 Andreas Wacknitz
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= mpg123
COMPONENT_VERSION= 1.32.7
COMPONENT_SUMMARY= Fast console MPEG Audio Player and decoder library
COMPONENT_PROJECT_URL= https://mpg123.org
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/download/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:3c8919243707951cac0e3c39bbf28653bcaffc43c98ff16801a27350db8f0f21
COMPONENT_SIG_URL= $(COMPONENT_ARCHIVE_URL).sig
COMPONENT_FMRI= audio/mpg123
COMPONENT_CLASSIFICATION= Applications/Sound and Video
COMPONENT_LICENSE= GPL-2.0-only OR LGPL-2.1-only
COMPONENT_LICENSE_FILE=  COPYING

include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(XPG6MODE)
CFLAGS += $(CPP_LARGEFILES)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-int-quality
CONFIGURE_OPTIONS += --enable-fifo
CONFIGURE_OPTIONS += --enable-network
CONFIGURE_OPTIONS += --enable-ipv6=yes
CONFIGURE_OPTIONS += --with-optimization=3
ifeq ($(strip $(MACH)),i386)
CONFIGURE_OPTIONS += --with-cpu=x86-64
endif
CONFIGURE_OPTIONS += --with-default-audio=pulse

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/openal
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
