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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		x265
COMPONENT_VERSION=	3.1.1
COMPONENT_SUMMARY=	High Efficiency Video Coding (HEVC)
COMPONENT_PROJECT_URL=	http://x265.org/
COMPONENT_FMRI=		library/video/x265
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_SRC=          $(COMPONENT_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://bitbucket.org/multicoreware/x265/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:827900c7cc0a0105b8a96460fab7cd22b97afa7b2835b5cb979c44bddaa3c8d0
COMPONENT_LICENSE=	GPLv2.0
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

SOURCE_DIR =    $(COMPONENT_DIR)/$(COMPONENT_SRC)/source/

CMAKE_OPTIONS += -DENABLE_PIC=ON
CMAKE_OPTIONS += -DENABLE_TESTS=ON

COMPONENT_TEST_CMD = test/TestBench

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += developer/assembler/nasm
# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
