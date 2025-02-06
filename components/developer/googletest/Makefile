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
# Copyright 2024 Andreas Wacknitz
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			googletest
COMPONENT_VERSION=		1.15.2
COMPONENT_SUMMARY=		Google test framework
COMPONENT_PROJECT_URL=	https://google.github.io/googletest/
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:7b42b4d6ed48810c5362c265a17faebe90dc2373c885e5216439d37927f02926
COMPONENT_ARCHIVE_URL=	https://github.com/google/googletest/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			developer/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Development/C++
COMPONENT_LICENSE=	 	BSD-3-Clause
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

DROP_STATIC_LIBRARIES= yes

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
