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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= openal
COMPONENT_VERSION= 1.16.0
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= OpenAL is a cross-platform 3D audio API
COMPONENT_SRC= $(COMPONENT_NAME)-soft-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:2f3dcd313fe26391284fbf8596863723f99c65d6c6846dccb48e79cadaf40d5f
COMPONENT_ARCHIVE_URL= \
  http://kcat.strangesoft.net/openal-releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://kcat.strangesoft.net/openal.html
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_FMRI = library/audio/openal

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/cmake.mk
include $(WS_TOP)/make-rules/ips.mk

CMAKE_OPTIONS += -DSSE=OFF
CMAKE_OPTIONS += -DEXAMPLES:INTERNAL=OFF

CMAKE_OPTIONS.64 = -DLIB_SUFFIX=/$(MACH64)
CMAKE_OPTIONS += $(CMAKE_OPTIONS.$(BITS))

$(INSTALL_32):	$(INSTALL_64)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
