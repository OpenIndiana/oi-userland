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

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         mtxclient
COMPONENT_VERSION=      0.9.2
COMPONENT_REVISION=		2
COMPONENT_SUMMARY=      Client API library for the Matrix protocol
COMPONENT_PROJECT_URL=  https://github.com/Nheko-Reborn/mtxclient
COMPONENT_FMRI=         network/chat/mtxclient
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:f55827fdba226c6fc409cf000c72b13cc6d069ec1300283a7239aa19c90c5f56
COMPONENT_ARCHIVE_URL=	https://github.com/Nheko-Reborn/$(COMPONENT_NAME)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= LICENSE

# Tests require Googletest which we don't have yet.
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DBUILD_LIB_TESTS=OFF
CMAKE_OPTIONS += -DBUILD_LIB_EXAMPLES=OFF

# Manually added build dependencies
REQUIRED_PACKAGES += library/c++/nlohmann-json

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/spdlog
REQUIRED_PACKAGES += library/olm
REQUIRED_PACKAGES += library/re2
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/coeurl
