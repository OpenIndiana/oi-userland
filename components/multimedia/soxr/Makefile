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

COMPONENT_NAME= soxr
COMPONENT_VERSION= 0.1.2
COMPONENT_SUMMARY= The SoX Resampler library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)-Source
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:54e6f434f1c491388cd92f0e3c47f1ade082cc24327bdc43762f7d1eefe0c275
COMPONENT_ARCHIVE_URL= \
  https://downloads.sourceforge.net/project/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://soxr.sourceforge.net/
COMPONENT_FMRI = library/audio/soxr
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING.LGPL

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CMAKE_OPTIONS += -DLIB_INSTALL_DIR=$(CMAKE_LIBDIR.$(BITS))
CMAKE_OPTIONS += -DBIN_INSTALL_DIR=$(CMAKE_BINDIR.$(BITS))

COMPONENT_TEST_TRANSFORMS += \
        '-e "s/\s\s*[0-9][0-9]*\.[0-9][0-9]* sec/ SEC sec/"' \
        '-e "/Test project/d"' \
        '-e "/^[mM]ake/d"' \
        '-e "s|^make.*: Leaving directory.*$$|XXX_REMOVE_XXX|g" ' \
        '-e "s|^make.*: Entering directory.*$$|XXX_REMOVE_XXX|g" ' \

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
