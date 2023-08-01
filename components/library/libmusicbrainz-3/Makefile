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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libmusicbrainz
COMPONENT_VERSION= 3.0.3
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= Software library for accessing MusicBrainz servers
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:7fd459a9fd05be9faec60a9a21caa9a1e9fda03147d58d8c7c95f33582a738c5
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.musicbrainz.org/pub/musicbrainz/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://musicbrainz.org/doc/libmusicbrainz
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_FMRI = library/musicbrainz/libmusicbrainz-3
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_LICENSE_FILE = COPYING.txt

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CXXFLAGS+= -std=c++11

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DCMAKE_VERBOSE_MAKEFILE=1

CMAKE_OPTIONS.64 += -DLIB_SUFFIX=/$(MACH64)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/musicbrainz/libdiscid
REQUIRED_PACKAGES += library/neon
REQUIRED_PACKAGES += system/library
