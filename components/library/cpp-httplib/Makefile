#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2024 Friedrich Kink
#

BUILD_STYLE=		cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         cpp-httplib
COMPONENT_VERSION=      0.18.3
COMPONENT_SUMMARY=      A C++ header-only HTTP/HTTPS server and client library 
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:a0567bcd6c3fe5cef1b329b96245119047f876b49e06cc129a36a7a8dffe173e
COMPONENT_ARCHIVE_URL=	https://github.com/yhirose/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://github.com/yhirose/$(COMPONENT_NAME)
COMPONENT_FMRI=         library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

LDFLAGS +=	 -lsocket

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON
CMAKE_OPTIONS += -DHTTPLIB_REQUIRE_OPENSSL=ON
CMAKE_OPTIONS += -DHTTPLIB_REQUIRE_ZLIB=ON
CMAKE_OPTIONS += -DHTTPLIB_REQUIRE_BROTLI=ON
CMAKE_OPTIONS += -DHTTPLIB_COMPILE=ON
CMAKE_OPTIONS += -DHTTPLIB_TEST=ON

# Do not change the order of these regexp transforms.
COMPONENT_TEST_TRANSFORMS += \
    '-e "/Test /d" ' \
    '-e "/ Start/d" ' \
    '-e "/^Output/d" ' \
    '-e "/^Errors/d" ' \
    '-e "/^Use /d" '

# manually added packages
REQUIRED_PACKAGES += developer/googletest

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
