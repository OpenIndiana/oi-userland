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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= portmidi
COMPONENT_VERSION= 217
IPS_COMPONENT_VERSION= 0.$(COMPONENT_VERSION)
COMPONENT_SUMMARY= library for real time input and output of MIDI data
COMPONENT_SRC= $(COMPONENT_NAME)
COMPONENT_ARCHIVE= $(COMPONENT_SRC)-src-$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH= \
  sha256:08e9a892bd80bdb1115213fb72dc29a7bf2ff108b378180586aa65f3cfd42e0f
COMPONENT_ARCHIVE_URL= \
  http://downloads.sourceforge.net/project/portmedia/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://portmedia.sourceforge.net/
COMPONENT_FMRI = library/portmidi
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = license.txt

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION += (cp -r $(COMPONENT_DIR)/files/* $(COMPONENT_SRC))

CMAKE_OPTIONS += -DPROJECT_BINARY_DIR=Release
CMAKE_OPTIONS += -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY="$(BUILD_DIR_$(BITS))/Release"
CMAKE_OPTIONS += -DCMAKE_LIBRARY_OUTPUT_DIRECTORY="$(BUILD_DIR_$(BITS))/Release"
CMAKE_OPTIONS += -DCMAKE_RUNTIME_OUTPUT_DIRECTORY="$(BUILD_DIR_$(BITS))/Release"


build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
