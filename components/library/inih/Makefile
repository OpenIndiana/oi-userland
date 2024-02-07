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
# Copyright 2023 Andreas Wacknitz
#

BUILD_BITS= 64_and_32
BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= inih
COMPONENT_VERSION= 57
HUMAN_VERSION= r$(COMPONENT_VERSION)
COMPONENT_SUMMARY= inih (INI Not Invented Here) is a simple .INI file parser written in C 
COMPONENT_SRC= $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL= https://github.com/benhoyt/inih
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:f03f98ca35c3adb56b2358573c8d3eda319ccd5287243d691e724b7eafa970b3
COMPONENT_FMRI= library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Development/C
COMPONENT_LICENSE= BSD 3-Clause
COMPONENT_LICENSE_FILE= LICENSE.txt

# Tests don't work with our machinery yet.
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_TEST_CMD= ( cd $(SOURCE_DIR)/tests && $(SH) unittest.sh )
COMPONENT_TEST_DIR= tests

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
