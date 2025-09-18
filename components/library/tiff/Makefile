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
# Copyright 2017 Alexander Pyhalov
#

BUILD_BITS= 64_and_32
USE_COMMON_TEST_MASTER= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= tiff
COMPONENT_VERSION= 4.7.1
COMPONENT_SUMMARY= libtiff - library for reading and writing TIFF
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:f698d94f3103da8ca7438d84e0344e453fe0ba3b7486e04c5bf7a9a3fabe9b69
COMPONENT_ARCHIVE_URL=	https://download.osgeo.org/libtiff/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.simplesystems.org/libtiff/
COMPONENT_FMRI=	image/library/libtiff
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE=	BSD-like
COMPONENT_LICENSE_FILE=	LICENSE.md

include $(WS_MAKE_RULES)/common.mk

# build with the distribution preferred libjpeg implementation
CFLAGS            +=    $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS          +=    $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS           +=    $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-cxx
CONFIGURE_OPTIONS += --disable-dependency-tracking

COMPONENT_POST_INSTALL_ACTION= ( \
	cd $(PROTOUSRDIR) ; \
	$(MV) include/tiffconf.h include/tiffconf-$(BITS).h );

COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRBINDIR32);

COMPONENT_TEST_ENV+= PATH=$(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)/32
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/freeglut
