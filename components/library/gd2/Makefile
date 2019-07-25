#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright 2016 Jim Klimov
# Copyright 2017 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gd2
COMPONENT_VERSION=	2.2.4
COMPONENT_REVISION=	6
COMPONENT_FMRI=		library/gd
COMPONENT_SUMMARY=	The Graphics Draw Library
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_PROJECT_URL=	http://libgd.github.io/
COMPONENT_SRC_NAME=	gd
COMPONENT_SRC=		libgd-$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:afdd50db677648cb9335b2dda10dd3a6700d97feb21fe802e6ee0f7065acd8c4
COMPONENT_ARCHIVE_URL=	https://github.com/libgd/libgd/archive/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GD2 License

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CFLAGS     += $(CPP_LARGEFILES)
CPPFLAGS   += $(CPP_LARGEFILES)

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

# Pass iconv related macro not set with CMake
CFLAGS   += -DHAVE_ICONV_T_DEF=1

COMPONENT_PREP_ACTION = (cp files/unitialized_memory_read.gif $(COMPONENT_SRC)/tests/gif)

# Needed for the test suite
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CMAKE_BINDIR.32 = bin/$(MACH32)

CMAKE_OPTIONS+= -DCMAKE_CPP_FLAGS="$(CPPFLAGS)"
CMAKE_OPTIONS+= -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS+= -DCMAKE_INSTALL_INCLUDEDIR=$(CMAKE_INCLUDEDIR)/$(COMPONENT_NAME)
CMAKE_OPTIONS+= -DCMAKE_INSTALL_DOCDIR=$(CMAKE_DOCDIR)/$(COMPONENT_NAME)
CMAKE_OPTIONS+= -DBUILD_STATIC_LIBS=OFF
CMAKE_OPTIONS+= -DBUILD_TEST=1
CMAKE_OPTIONS+= -DENABLE_FONTCONFIG=ON
CMAKE_OPTIONS+= -DENABLE_FREETYPE=ON
CMAKE_OPTIONS+= -DFREETYPE_INCLUDE_DIRS=/usr/include/freetype2
CMAKE_OPTIONS+= -DENABLE_ICONV=ON
CMAKE_OPTIONS+= -DICONV_INCLUDE_DIR=/usr/include
CMAKE_OPTIONS+= -DENABLE_JPEG=ON
# Tests fail in 64-bit if not specified explicitly
CMAKE_OPTIONS+= -DJPEG_INCLUDE_DIR=$(JPEG_INCDIR)
CMAKE_OPTIONS+= -DJPEG_LIBRARY=$(JPEG_LIBDIR)/libjpeg.so
# Features
CMAKE_OPTIONS+= -DENABLE_LIQ=OFF
CMAKE_OPTIONS+= -DENABLE_PNG=ON
CMAKE_OPTIONS+= -DENABLE_TIFF=ON
CMAKE_OPTIONS+= -DENABLE_WEBP=ON
CMAKE_OPTIONS+= -DENABLE_XPM=ON

COMPONENT_TEST_ENV_CMD =
COMPONENT_TEST_CMD     = (cd $(@D)/tests; ctest .)
COMPONENT_TEST_TARGETS =

COMPONENT_TEST_TRANSFORMS = \
	'-e "s/[0-9.]* sec//g"' \
	'-n' \
	'-e "/Passed/p"' \
	'-e "/Failed/p"'

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Test failures:
# 32  64  Test
# X   X     6 - test_freetype_bug00132 (Failed): Different Freetype rendering
# X        36 - test_gdimagecopyresampled_bug00201 (Failed): Visually similar
# X        65 - test_gdimagegrayscale_basic (Failed): Visually similar
# X        88 - test_gdimagerotate_bug00067 (Failed): Visually similar
# X   X   101 - test_gdimagestringft_gdimagestringft_bbox (Failed): Different Freetype rendering
test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libxpm
