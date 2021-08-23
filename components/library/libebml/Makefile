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
# Copyright (c) 2015 Alexander Pyhalov
# Copyright (c) 2019 Michal Nowak
# Copyright (c) 2021 Andreas Wacknitz
#

BUILD_BITS=				32_and_64
BUILD_STYLE=			cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libebml
COMPONENT_VERSION=      1.4.2
COMPONENT_PROJECT_URL=  https://matroska-org.github.io/libebml/
COMPONENT_SUMMARY=      Extensible Binary Markup Language
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:41c7237ce05828fb220f62086018b080af4db4bb142f31bec0022c925889b9f2
COMPONENT_ARCHIVE_URL=	https://dl.matroska.org/downloads/libebml/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		LGPLv2.1
COMPONENT_LICENSE_FILE=	LICENSE.LGPL
COMPONENT_FMRI=			library/libebml
COMPONENT_CLASSIFICATION=	System/Libraries

TEST_TARGET:		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DBUILD_SHARED_LIBS:BOOL=ON
CMAKE_OPTIONS += -DSTATIC_BUILD:BOOL=OFF

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
