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
# Copyright 2025 Friedrich Kink
#

BUILD_STYLE=		cmake
DROP_STATIC_LIBRARIES= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         flatbuffers
COMPONENT_VERSION=      25.9.23
COMPONENT_SUMMARY=      FlatBuffers: Memory Efficient Serialization Library 
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:9102253214dea6ae10c2ac966ea1ed2155d22202390b532d1dea64935c518ada
COMPONENT_ARCHIVE_URL=	https://github.com/google/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://flatbuffers.dev/
COMPONENT_FMRI=         library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      Apache-2.0
COMPONENT_LICENSE_FILE= LICENSE

COMPONENT_TEST_TARGETS= test
COMPONENT_TEST_TRANSFORMS += \
        "-e '/^Total Test time/d' " \
        "-e 's/[[:digit:]]\+\.[[:digit:]][[:digit:]].*$$//' "

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DFLATBUFFERS_BUILD_FLATHASH=ON
CMAKE_OPTIONS += -DFLATBUFFERS_BUILD_SHAREDLIB=ON

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
