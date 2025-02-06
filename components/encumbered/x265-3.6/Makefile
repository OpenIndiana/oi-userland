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
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         x265
COMPONENT_VERSION=      3.6
COMPONENT_SUMMARY=	Runtime library for High Efficiency Video Coding (HEVC) version $(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://x265.org/
COMPONENT_FMRI=         library/video/x265-36
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_SRC=          $(COMPONENT_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://bitbucket.org/multicoreware/$(COMPONENT_NAME)_git/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:663531f341c5389f460d730e62e10a4fcca3428ca2ca109693867bc5fe2e2807
COMPONENT_LICENSE=      GPLv2.0
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

SOURCE_DIR = $(COMPONENT_DIR)/$(COMPONENT_SRC)/source/

CMAKE_OPTIONS += -DENABLE_PIC=ON
CMAKE_OPTIONS += -DENABLE_TESTS=ON

COMPONENT_TEST_CMD = test/TestBench

# Manually added build dependencies
REQUIRED_PACKAGES += developer/assembler/nasm

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
