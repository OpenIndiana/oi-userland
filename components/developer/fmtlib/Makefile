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
# Copyright 2023 Friedrich Kink
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         fmt
COMPONENT_VERSION=      10.2.1
COMPONENT_SUMMARY=      fmt is an open-source formatting library providing a fast and safe alternative to C stdio and C++ iostreams.
COMPONENT_PROJECT_URL=  https://github.com/fmtlib/$(COMPONENT_NAME)
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=  https://github.com/$(COMPONENT_NAME)lib/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:1250e4cc58bf06ee631567523f48848dc4596133e163f02615c97f78bab6c811
COMPONENT_FMRI=         developer/fmt
COMPONENT_CLASSIFICATION=Development/Other Languages
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= LICENSE

PATH= $(PATH.gnu)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_ENV += TZ=UTC

# SPARC needs math library.
ifeq ($(MACH), sparc)
REQUIRED_PACKAGES += system/library/math
endif

CMAKE_OPTIONS += -DFMT_MASTER_PROJECT=ON
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON
CMAKE_OPTIONS += -DBUILD_STATIC_LIBS=OFF

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
