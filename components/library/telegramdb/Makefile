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
# Copyright 2022 David Stes
#

# currently build with gcc-11 instead of gcc-7 (out of memory with gcc-7)
# Tdlib provides a php script to SplitSources which may help in the gcc-7 case

# 1.8.0 is easier to build than 1.6.0
# the Illumos and Solaris platforms were added in 1.7.0 or 1.8.0 to config.h
# and platform.h so they are supported target platforms
# also see CMake/illumos.cmake in the TdLib sources

# because we currently need 1.6.0 in Squeak, the CMakeLists.txt
# config.h and platform.h is patched so that 1.6.0 builds (as 1.8.0 does)
# see www.squeak.org for more information for general info on Squeak
# also see http://docs.openindiana.org/handbook/community/squeak/index.html
# the Telegram Squeak Client is at
# https://github.com/hpi-swa-teaching/TelegramClient

BUILD_BITS=		32_and_64
BUILD_STYLE=		cmake
# USE_OPENSSL11=		yes
include ../../../make-rules/shared-macros.mk
GCC_VERSION= 		11

# the FMRI is telegramdb , the project is tdlib, component is td

COMPONENT_NAME=		td
COMPONENT_VERSION=	1.6.0
COMPONENT_SUMMARY=	Telegram Database Library
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=	https://core.telegram.org/tdlib
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:9dce57a96f9d4bac8f99aab13ef5cbf6fed04b234a5d22dfa7ef7dce06ea43f8
COMPONENT_ARCHIVE_URL=	https://github.com/tdlib/td/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		library/telegramdb
COMPONENT_LICENSE=	Boost Software License
COMPONENT_LICENSE_FILE= td.license

# there are tests in the tdlib but currently we don't run them yet
# we currently are at version 1.6.0 - that is what the Squeak client requires
# there is an open request upstream to support 1.8.0
TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS +=	-DCMAKE_C_COMPILER=$(CC)
CMAKE_OPTIONS +=	-DBIN_INSTALL_DIR=/usr/$(CMAKE_LIBDIR.$(BITS))
CMAKE_OPTIONS +=	-DLIB_INSTALL_DIR=/usr/$(CMAKE_LIBDIR.$(BITS))
CMAKE_OPTIONS +=	-DCMAKE_BUILD_TYPE=Release

REQUIRED_PACKAGES += developer/gperf
REQUIRED_PACKAGES += developer/gcc-11

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math

