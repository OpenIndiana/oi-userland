#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2021 Andreas Wacknitz
#

BUILD_BITS= 64_and_32
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         double-conversion
COMPONENT_VERSION=      3.4.0
COMPONENT_SUMMARY=      binary-decimal and decimal-binary routines for IEEE doubles
COMPONENT_PROJECT_URL=  https://github.com/google/double-conversion
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:42fd4d980ea86426e457b24bdfa835a6f5ad9517ddb01cdb42b99ab9c8dd5dc9
COMPONENT_ARCHIVE_URL=	https://github.com/google/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=			library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=		BSD 3-Clause
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DBUILD_SHARED_LIBS:BOOL=ON
CMAKE_OPTIONS += -DSTATIC_BUILD:BOOL=OFF
CMAKE_OPTIONS += -DBUILD_TESTING:BOOL=ON

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/[0-9]*\.[0-9]* sec//"'

# The math library is needed on SPARC and should be kept.
REQUIRED_PACKAGES += system/library/math

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
