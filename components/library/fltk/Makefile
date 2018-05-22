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

COMPONENT_NAME=        fltk
COMPONENT_VERSION=     1.3.4
COMPONENT_REL_VERSION=2
COMPONENT_REVISION=    1
COMPONENT_SUMMARY=     fltk - Fast Light Toolkit
COMPONENT_PROJECT_URL= http://www.fltk.org
COMPONENT_FMRI=        library/fltk
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-$(COMPONENT_REL_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-source.tar.gz
COMPONENT_ARCHIVE_URL= \
  http://fltk.org/pub/fltk/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:25d349c18c99508737d48f225a2eb26a43338f9247551cab72a317fa42cda910
COMPONENT_LICENSE= GPLv2

CONFIGURE_FIX_LIBTOOL_RPATH= no

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --disable-static

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrender
