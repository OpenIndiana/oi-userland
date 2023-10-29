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
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE = cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         abseil-cpp
COMPONENT_VERSION=      20230802.1
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      Collection of C++ library code designed to augment the C++ standard library
COMPONENT_PROJECT_URL=  https://abseil.io
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:987ce98f02eefbaf930d6e38ab16aa05737234d7afbab2d5c4ea7adbe50c28ed
COMPONENT_ARCHIVE_URL=	https://github.com/abseil/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=         library/c++/abseil-cpp
COMPONENT_CLASSIFICATION=       Development/C++
COMPONENT_LICENSE=      Apache
COMPONENT_LICENSE_FILE= LICENSE

# Tests require Googletest which we don't have yet.
TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
