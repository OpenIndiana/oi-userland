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
# Copyright 2017 Aurelien Larcher
#
PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         lensfun
COMPONENT_VERSION=      0.3.2
COMPONENT_SUMMARY=      Lensfun - library rectifying defects introduced by photographic equipment
COMPONENT_PROJECT_URL=  http://lensfun.sourceforge.net/
COMPONENT_FMRI=         image/library/lensfun  
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= \
  https://sourceforge.net/projects/lensfun/files/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_ARCHIVE_HASH= \
  sha256:ae8bcad46614ca47f5bda65b00af4a257a9564a61725df9c74cb260da544d331
COMPONENT_LICENSE=      GPLv3,LGPLv3

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CMAKE_OPTIONS+= -DCMAKE_BUILD_TYPE='Release'
CMAKE_OPTIONS+= -DBUILD_TESTS=ON
CMAKE_OPTIONS+= -DBUILD_LENSTOOL=ON
CMAKE_OPTIONS+= -DINSTALL_HELPER_SCRIPTS=OFF

COMPONENT_TEST_TRANSFORMS+= '-e "s/[0-9. ]*sec//g"'

build:    $(BUILD_32_and_64)

install:  $(INSTALL_32_and_64)

test:    $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
