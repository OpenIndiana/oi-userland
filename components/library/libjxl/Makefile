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
# Copyright 2026 isoriano1968
#

BUILD_STYLE=		cmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libjxl
COMPONENT_VERSION=	0.12.0
COMPONENT_SUMMARY=	JPEG XL image format library, with its gdk-pixbuf loader
COMPONENT_PROJECT_URL=	https://github.com/libjxl/libjxl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:03e9be69a30be4011f559da75328b6d7cea8ad921fabfbd551ce10bf45cdc992
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		image/library/libjxl
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE=	BSD-3-Clause
COMPONENT_LICENSE_FILE=	LICENSE

# The tests need the testdata submodule, which the release archive lacks
TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# The release archive has no third_party sources: use the system libraries
CMAKE_OPTIONS +=	-DJPEGXL_FORCE_SYSTEM_BROTLI=ON
CMAKE_OPTIONS +=	-DJPEGXL_FORCE_SYSTEM_HWY=ON
CMAKE_OPTIONS +=	-DJPEGXL_FORCE_SYSTEM_LCMS2=ON
# lcms2 on all platforms (skcms is little-endian only)
CMAKE_OPTIONS +=	-DJPEGXL_ENABLE_SKCMS=OFF
CMAKE_OPTIONS +=	-DJPEGXL_ENABLE_SJPEG=OFF
CMAKE_OPTIONS +=	-DJPEGXL_BUNDLE_LIBPNG=OFF
CMAKE_OPTIONS +=	-DBUILD_TESTING=OFF
# the gdk-pixbuf loader and thumbnailer
CMAKE_OPTIONS +=	-DJPEGXL_ENABLE_PLUGINS=ON
# no Java, no developer programs, no doxygen
CMAKE_OPTIONS +=	-DJPEGXL_ENABLE_JNI=OFF
CMAKE_OPTIONS +=	-DJPEGXL_ENABLE_BENCHMARK=OFF
CMAKE_OPTIONS +=	-DJPEGXL_ENABLE_EXAMPLES=OFF
CMAKE_OPTIONS +=	-DJPEGXL_ENABLE_DOXYGEN=OFF
CMAKE_OPTIONS +=	-DJPEGXL_ENABLE_OPENEXR=OFF

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/giflib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/highway
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
