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

BUILD_BITS=				32_and_64
BUILD_STYLE=			cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         double-conversion
COMPONENT_VERSION=      3.1.5
COMPONENT_PROJECT_URL=  https://github.com/google/double-conversion
COMPONENT_SUMMARY=      binary-decimal and decimal-binary routines for IEEE doubles
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:a63ecb93182134ba4293fd5f22d6e08ca417caafa244afaa751cbfddf6415b13
COMPONENT_ARCHIVE_URL=	https://github.com/google/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=		BSD 3-Clause
COMPONENT_FMRI=			library/double-conversion
COMPONENT_CLASSIFICATION=	System/Libraries

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DBUILD_SHARED_LIBS:BOOL=ON
CMAKE_OPTIONS += -DSTATIC_BUILD:BOOL=OFF
CMAKE_OPTIONS += -DBUILD_TESTING:BOOL=ON

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
