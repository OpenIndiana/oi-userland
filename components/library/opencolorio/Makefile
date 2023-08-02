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

BUILD_BITS=		64
BUILD_STYLE=	cmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		OpenColorIO
COMPONENT_VERSION=	2.1.1
COMPONENT_REVISION= 1
COMPONENT_FMRI=		library/opencolorio
COMPONENT_PROJECT_URL=	https://github.com/AcademySoftwareFoundation/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	A color management framework for visual effects and animation
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:16ebc3e0f21f72dbe90fe60437eb864f4d4de9c255ef8e212f837824fc9b8d9c
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	BSD 3-Clause
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk
PATH=$(PATH.gnu)
CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX=/usr
CMAKE_OPTIONS += -DCMAKE_INSTALL_LIBDIR=lib/amd64
CMAKE_OPTIONS += -DCMAKE_DISABLE_FIND_PACKAGE_OpenImageIO=TRUE
CMAKE_OPTIONS += -DCMAKE_C_FLAGS="$(CFLAGS)"
CMAKE_OPTIONS += -DCMAKE_CXX_FLAGS="$(CXXFLAGS)"
CMAKE_OPTIONS += -DCMAKE_SKIP_RPATH=TRUE

# Build dependencies
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/pystring
REQUIRED_PACKAGES += library/python/pybind11
REQUIRED_PACKAGES += library/yaml-cpp

# Manually added dependencies
REQUIRED_PACKAGES += library/tinyxml
REQUIRED_PACKAGES += x11/library/freeglut
REQUIRED_PACKAGES += x11/library/libglew

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/imath
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/pystring
REQUIRED_PACKAGES += library/yaml-cpp
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
