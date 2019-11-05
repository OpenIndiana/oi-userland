#! /usr/bin/sh
#
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
# Copyright 2014 Andrzej Szeszo.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		poppler
COMPONENT_VERSION=	0.56.0
COMPONENT_REVISION=	6
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
     sha256:869dbadf99ed882e776acbdbc06689d8a81872a2963440b1e8516cd7a2577173
COMPONENT_ARCHIVE_URL= \
     http://poppler.freedesktop.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://poppler.freedesktop.org/
COMPONENT_FMRI=		library/libpoppler
COMPONENT_SUMMARY=	Poppler is a PDF rendering library based on the xpdf-3.0 code base
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_INSTALL_ACTION += \
	$(RM) $(PROTO_DIR)$(CONFIGURE_LIBDIR.$(BITS))/*.{a,la}

CFLAGS += $($(COMPILER)_C99_ENABLE)

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

# Find issues with undefined symbols in build time
LD_OPTIONS += $(LD_Z_DEFS)

CONFIGURE_OPTIONS += CPPFLAGS="$(CPP_XPG6MODE) $(CPP_LARGEFILES)"
CONFIGURE_OPTIONS += CXX="$(CXX) $($(COMPILER)_NORUNPATH)"
CONFIGURE_OPTIONS += --enable-poppler-glib
CONFIGURE_OPTIONS += --disable-poppler-qt4
CONFIGURE_OPTIONS += --disable-poppler-qt5
CONFIGURE_OPTIONS += --enable-zlib
CONFIGURE_OPTIONS += --enable-xpdf-headers

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CXX="$(CXX)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += image/library/openjpeg
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/mozilla-nss
