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

BUILD_BITS= 32_and_64
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= soxr
COMPONENT_VERSION= 0.1.3
COMPONENT_SUMMARY= The SoX Resampler library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)-Source
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:b111c15fdc8c029989330ff559184198c161100a59312f5dc19ddeb9b5a15889
COMPONENT_ARCHIVE_URL= \
	https://downloads.sourceforge.net/project/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://soxr.sourceforge.net/
COMPONENT_FMRI = library/audio/soxr
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING.LGPL

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DLIB_INSTALL_DIR=$(CMAKE_LIBDIR.$(BITS))
CMAKE_OPTIONS += -DBIN_INSTALL_DIR=$(CMAKE_BINDIR.$(BITS))

COMPONENT_TEST_TRANSFORMS += \
        '-e "s/\s\s*[0-9][0-9]*\.[0-9][0-9]* sec/ SEC sec/"' \
        '-e "/Test project/d"' \
        '-e "/^[mM]ake/d"' \
        '-e "s|^make.*: Leaving directory.*$$|XXX_REMOVE_XXX|g" ' \
        '-e "s|^make.*: Entering directory.*$$|XXX_REMOVE_XXX|g" ' \

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
