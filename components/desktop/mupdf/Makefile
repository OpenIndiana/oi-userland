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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         mupdf
COMPONENT_VERSION=      1.11
COMPONENT_SUMMARY=      MuPDF is a lightweight PDF, XPS, and E-book viewer
COMPONENT_PROJECT_URL=  https://mupdf.com/
COMPONENT_FMRI=         desktop/pdf-viewer/mupdf
COMPONENT_CLASSIFICATION=Applications/Office
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)-source
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= \
  https://mupdf.com/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:209474a80c56a035ce3f4958a63373a96fad75c927c7b1acdc553fc85855f00a
COMPONENT_LICENSE=      AGPL

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION= ( cd $(@D); rm -rf thirdparty/{curl,freetype,glfw,harfbuzz,libjpeg,zlib} )

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

COMPONENT_BUILD_ENV+= CC="$(CC) "
COMPONENT_BUILD_ENV+= CFLAGS="$(CFLAGS) "
COMPONENT_BUILD_ENV+= CXX="$(CXX) "
COMPONENT_BUILD_ENV+= CXXFLAGS="$(CXXFLAGS) "
COMPONENT_BUILD_ENV+= LDFLAGS="$(LDFLAGS) "
COMPONENT_BUILD_ENV+= PKG_CONFIG_PATH="$(PKG_CONFIG_PATH) "

COMPONENT_BUILD_TARGETS= build=release
COMPONENT_INSTALL_TARGETS= build=release prefix="$(USRDIR)" libdir="$(USRLIBDIR$(BITS))"  install

build:    $(BUILD_64)

install:  $(INSTALL_64)

test:    $(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
