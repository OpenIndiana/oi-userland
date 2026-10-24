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

COMPONENT_NAME=		spirv-headers
COMPONENT_VERSION=	1.4.304.0
COMPONENT_SUMMARY=	SPIR-V headers
COMPONENT_PROJECT_URL=	https://registry.khronos.org/SPIR-V/
COMPONENT_SRC=		SPIRV-Headers-vulkan-sdk-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	vulkan-sdk-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/KhronosGroup/SPIRV-Headers/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:162b864ebaf339d66953fc2c4ad974bc4f453e0f04155cd3755a85e33f408eee
COMPONENT_FMRI=		x11/library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX=$(USRDIR)

# Auto-generated dependencies
