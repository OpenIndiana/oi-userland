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
# Copyright 2016 phorcys@126.com.  All rights reserved.
# Copyright 2021 Andreas Wacknitz
# Copyright 2023 Niklas Poslovski
#

BUILD_BITS=	32_and_64
BUILD_STYLE=	cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= taglib
COMPONENT_VERSION= 1.13
COMPONENT_FMRI=	library/audio/taglib
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_PROJECT_URL=	https://taglib.github.io/
COMPONENT_SUMMARY=	taglib - a library for reading and editing the meta-data of several popular audio formats.
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:58f08b4db3dc31ed152c04896ee9172d22052bc7ef12888028c01d8b1d60ade0
COMPONENT_ARCHIVE_URL=	https://taglib.github.io/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= LGPL

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
