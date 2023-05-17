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
# Copyright 2017 Carsten Grzemba
#

BUILD_BITS= 64_and_32
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= exiv2
COMPONENT_VERSION= 0.27.7
COMPONENT_SUMMARY= Image metadata library and tools
COMPONENT_PROJECT_URL= https://www.exiv2.org
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:551b1266e3aabd321f6d555dccd776128ee449d5039feafee927a1f33f7a9753
COMPONENT_ARCHIVE_URL= https://github.com/Exiv2/exiv2/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI= image/library/exiv2
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

# We don't have GTest
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# We don't have GTest
#CMAKE_OPTIONS += -DEXIV2_BUILD_UNIT_TESTS=On

# iconv-0.27 has an outdated, erratic FindIconv.cmake, remove this:
# See https://www.illumos.org/issues/13824#change-40077 for details.
COMPONENT_POST_UNPACK_ACTION += \
	$(RM) $(SOURCE_DIR)/cmake/FindIconv.cmake

LDFLAGS += -lnsl -lsocket

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
