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
# Copyright 2022 Daniel Chan
#

BUILD_BITS=		32_and_64
BUILD_STYLE=	cmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Imath
COMPONENT_VERSION=	3.1.5
COMPONENT_FMRI=		library/imath
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=	https://github.com/AcademySoftwareFoundation/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	C++ representation of 2D and 3D vectors
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:1e9c7c94797cf7b7e61908aed1f80a331088cc7d8873318f70376e4aed5f25fb
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	BSD 3-Clause
COMPONENT_LICENSE_FILE=	LICENSE.md

TEST_TARGET=		$(NO_TEST)
include $(WS_MAKE_RULES)/common.mk
PATH=$(PATH.gnu)
CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX=/usr
CMAKE_OPTIONS.32 += -DCMAKE_INSTALL_LIBDIR=lib
CMAKE_OPTIONS.64 += -DCMAKE_INSTALL_LIBDIR=lib/amd64

# Build dependencies
REQUIRED_PACKAGES += library/qt5
# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
