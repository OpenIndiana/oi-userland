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
# Copyright 2017 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= brotli
COMPONENT_VERSION= 0.6.0
COMPONENT_SUMMARY=  Library for generic-purpose lossless compression algorithm
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:69cdbdf5709051dd086a2f020f5abf9e32519eafe0ad6be820c667c3a9c9ee0f
COMPONENT_ARCHIVE_URL= \
  https://github.com/google/brotli/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL = https://github.com/google/brotli
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_FMRI = library/brotli
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CMAKE_BINDIR.64=$(CMAKE_BINDIR.32)

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DCMAKE_VERBOSE_MAKEFILE=1

CMAKE_OPTIONS.64 += -DLIB_SUFFIX=/$(MACH64)

#Overwrite 32-bit binaries with 64-bit ones
$(BUILD_64):	$(BUILD_32)

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
# Strip times from test output, since they're always different
COMPONENT_TEST_TRANSFORMS += '-e "s%\([0-9\.]\)* sec%%"'

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
