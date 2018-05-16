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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=        pugixml
COMPONENT_VERSION=     1.9
COMPONENT_REVISION=    1
COMPONENT_SUMMARY=     pugixml - light-weight C++ XML processing library
COMPONENT_PROJECT_URL= https://pugixml.org/
COMPONENT_FMRI=        library/pugixml
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= \
  http://github.com/zeux/pugixml/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:d156d35b83f680e40fd6412c4455fdd03544339779134617b9b28d19e11fdba6
COMPONENT_LICENSE=     MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CMAKE_OPTIONS+= -DBUILD_SHARED_LIBS=ON
CMAKE_OPTIONS+= -DBUILD_TESTS=OFF
CMAKE_OPTIONS+= -DBUILD_PKGCONFIG=ON

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
