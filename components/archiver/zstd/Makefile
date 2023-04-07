#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2019 Michal Nowak
# Copyright 2020 Nona Hansel
# Copyright 2021 Marco van Wieringen
#

BUILD_BITS= 64_and_32
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zstd
COMPONENT_VERSION=	1.5.5
COMPONENT_SUMMARY=	Zstandard, or zstd for short, is a fast lossless compression algorithm, targeting real-time compression scenarios
COMPONENT_PROJECT_URL=	https://facebook.github.io/zstd/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/facebook/zstd/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:9c4396cc829cfae319a6e2615202e82aad41372073482fce286fac78646d3ee4
COMPONENT_FMRI=		compress/zstd
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	BSD,GPLv2.0

include $(WS_MAKE_RULES)/common.mk

CMAKE_ASM_FLAGS.32 = -m32
CMAKE_ASM_FLAGS.64 = -m64

CMAKE_OPTIONS += -DCMAKE_ASM_FLAGS=$(CMAKE_ASM_FLAGS.$(BITS))

# Test suite expect files files not to be symlinks
COMPONENT_PRE_CMAKE_ACTION= ( cp -a $(SOURCE_DIR)/* $(@D) )

# CMake files are in build/cmake directory,
# hence mangle with 'configure' target
$(BUILD_DIR)/%/.configured:     $(SOURCE_DIR)/.prep
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(COMPONENT_PRE_CMAKE_ACTION)
	(cd $(@D) ; $(ENV) $(CMAKE_ENV) \
		$(CMAKE) $(CMAKE_OPTIONS) $(COMPONENT_DIR)/$(COMPONENT_SRC)/build/cmake/)
	$(COMPONENT_POST_CMAKE_ACTION)
	$(TOUCH) $@

# Use make targets for tests directly
COMPONENT_TEST_CMD=	$(GMAKE)
COMPONENT_TEST_ARGS=	-C
COMPONENT_TEST_TARGETS=	tests test-zstd
COMPONENT_TEST_ENV=	$(CMAKE_ENV)

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
