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
# Copyright 2017 Gary Mills
# Copyright 2017 Alexander Pyhalov
#

BUILD_BITS= 64_and_32
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= openal
COMPONENT_VERSION= 1.17.0
COMPONENT_SUMMARY= OpenAL is a cross-platform 3D audio API
COMPONENT_PROJECT_URL= https://openal-soft.org/
COMPONENT_SRC= $(COMPONENT_NAME)-soft-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:ca1900969b53f0526b45dbd32ec444bd246186e638c5b7be48834cefbc23dfc1
COMPONENT_ARCHIVE_URL= https://github.com/kcat/openal-soft/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= library/audio/openal
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE= LGPLv2
COMPONENT_LICENSE_FILE= COPYING

#TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_UNPACK_ACTION= \
	$(MV) $(COMPONENT_NAME)-soft-$(COMPONENT_SRC) $(COMPONENT_SRC)

# This is needed to be able to use scandir():
CFLAGS += $(CPP_XPG6MODE)

CMAKE_OPTIONS += -DEXAMPLES:INTERNAL=OFF

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/sdl-sound
REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
