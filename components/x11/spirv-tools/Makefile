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
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		spirv-tools
COMPONENT_VERSION=	2024.4
COMPONENT_SUMMARY=	API and commands for processing SPIR-V modules
COMPONENT_PROJECT_URL=	https://www.khronos.org/spir/
COMPONENT_SRC=		SPIRV-Tools-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/KhronosGroup/SPIRV-Tools/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:8620a1ff8886b9ed33905464b085c444725597c1115242e0b82e213b7b3558a1
COMPONENT_FMRI=		x11/library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_LICENSE=	Apache-2.0
COMPONENT_LICENSE_FILE=	LICENSE

# The libraries have unversioned sonames (libSPIRV-Tools.so): rebuild glslang
# and mesa, which link them, with every update.

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX=$(USRDIR)
CMAKE_OPTIONS += -DCMAKE_INSTALL_LIBDIR=lib/amd64
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=none
CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON
CMAKE_OPTIONS += -DSPIRV_TOOLS_BUILD_STATIC=OFF
CMAKE_OPTIONS += -DSPIRV-Headers_SOURCE_DIR=/usr
# GCC 14 reports a false -Wstringop-overflow in source/opt (amd_ext_to_khr.cpp).
CMAKE_OPTIONS += -DSPIRV_WERROR=OFF

COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9. ]*sec//g"'

# Build dependencies
REQUIRED_PACKAGES += x11/library/spirv-headers

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
