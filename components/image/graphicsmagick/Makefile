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
# Copyright (c) 2017 Dariusz Sendkowski
#

BUILD_BITS=	32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		GraphicsMagick
COMPONENT_MAJOR_VERSION=1.3
COMPONENT_MINOR_VERSION=38
COMPONENT_VERSION=	$(COMPONENT_MAJOR_VERSION).$(COMPONENT_MINOR_VERSION)
COMPONENT_PROJECT_URL=	http://www.graphicsmagick.org/	
COMPONENT_SUMMARY=	A collection of utilities to support file format conversion,image processing, and 2D vector rendering.
COMPONENT_FMRI=		image/graphicsmagick
COMPONENT_CLASSIFICATION=Applications/Graphics and Imaging
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:d60cd9db59351d2b9cb19beb443170acaa28f073d13d258f67b3627635e32675
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/graphicsmagick/files/graphicsmagick/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	Copyright.txt

include $(WS_MAKE_RULES)/common.mk

CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared

unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/=========/p" ' \
	'-e "/Testsuite summary for/p" ' \
	'-e "/TOTAL/p" ' \
	'-e "/PASS/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" '

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += codec/jasper
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
