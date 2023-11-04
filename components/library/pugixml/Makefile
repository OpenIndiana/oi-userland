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
# Copyright 2018 Aurelien Larcher
#

BUILD_BITS= 64
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=        pugixml
COMPONENT_VERSION=     1.14
COMPONENT_REVISION=    1
COMPONENT_SUMMARY=     pugixml - light-weight C++ XML processing library
COMPONENT_PROJECT_URL= https://pugixml.org/
COMPONENT_SRC=         $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=     $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= https://github.com/zeux/pugixml/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:2f10e276870c64b1db6809050a75e11a897a8d7456c4be5c6b2e35a11168a015
COMPONENT_FMRI=        library/pugixml
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=     MIT
COMPONENT_LICENSE_FILE= LICENSE.md

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON
CMAKE_OPTIONS += -DBUILD_TESTS=OFF
CMAKE_OPTIONS += -DBUILD_PKGCONFIG=ON

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
