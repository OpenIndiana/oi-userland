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

COMPONENT_NAME=		glslang
COMPONENT_VERSION=	14.3.0
COMPONENT_SUMMARY=	OpenGL and OpenGL ES shader front end and validator
COMPONENT_PROJECT_URL=	https://github.com/KhronosGroup/glslang
COMPONENT_SRC=		glslang-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/KhronosGroup/glslang/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:be6339048e20280938d9cb399fcdd06e04f8654d43e170e8cce5a56c9a754284
COMPONENT_FMRI=		x11/library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_LICENSE=	BSD-3-Clause
COMPONENT_LICENSE_FILE=	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX=$(USRDIR)
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=none
CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON
CMAKE_OPTIONS += -DSPIRV_TOOLS_BUILD_STATIC=OFF
CMAKE_OPTIONS += -DALLOW_EXTERNAL_SPIRV_TOOLS=ON
CMAKE_OPTIONS += -DGLSLANG_TEST=ON

COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9. ]*sec//g"'

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/spirv-tools
