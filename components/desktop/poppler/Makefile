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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		poppler
COMPONENT_VERSION=	0.33.0
COMPONENT_PROJECT_URL=	http://poppler.freedesktop.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:a5fa6d7f7dc5382b48caca82b147c54bdffda02698611af76db5326ba64995a6
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/poppler
TPNO_POPPLER=		25617

COMPONENT_NAME_1=	poppler-data
COMPONENT_VERSION_1=	0.4.7
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:e752b0d88a7aba54574152143e7bf76436a7ef51977c55d6bd9a48dccde3a7de
COMPONENT_ARCHIVE_URL_1= $(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE_1)
TPNO_POPPLER_DATA=	25618

TEST_TARGET= $(NO_TESTS)

# This version of poppler only works with the new version of evince.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = \
	(cd $(@D) ; \
	aclocal -I . ; \
	libtoolize --force --copy ; \
	autoheader ; \
	automake -a -c -f ; \
	autoconf )

# For now, all things built for C++11 require gcc.
# (Poppler provides a C++ wrapper.)
COMPILER=gcc
# Uses strcpy_s, etc. c11 functions.
CFLAGS += -std=c11
CXXFLAGS += -std=c++11 -D__STDC_WANT_LIB_EXT1__=1

# Reduce build time dependencies since we don't ship this and can't run as an
# automated test.
CONFIGURE_OPTIONS +=	--disable-gtk-test
CONFIGURE_OPTIONS +=	--disable-poppler-qt4
CONFIGURE_OPTIONS +=	--disable-poppler-qt5
CONFIGURE_OPTIONS +=	--disable-static
# --enable-zlib not recommended by developers?
CONFIGURE_OPTIONS +=	--disable-zlib
CONFIGURE_OPTIONS +=	--enable-cairo-output
CONFIGURE_OPTIONS +=	--enable-cms=lcms2
# Required for other components.
CONFIGURE_OPTIONS +=	--enable-introspection
CONFIGURE_OPTIONS +=	--enable-largefile
CONFIGURE_OPTIONS +=	--enable-libcurl
CONFIGURE_OPTIONS +=	--enable-libjpeg
CONFIGURE_OPTIONS +=	--enable-libpng
CONFIGURE_OPTIONS +=	--enable-libtiff
CONFIGURE_OPTIONS +=	--enable-poppler-cpp
CONFIGURE_OPTIONS +=	--enable-poppler-glib
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--enable-splash-output
CONFIGURE_OPTIONS +=	--enable-xpdf-headers
CONFIGURE_OPTIONS +=	--with-font-configuration=fontconfig
CONFIGURE_OPTIONS +=	--with-pic
CONFIGURE_OPTIONS +=	--with-x
# XXX clone test repo? ick.
#CONFIGURE_OPTIONS +=	--with-testdatadir=

# Install the poppler data files.
COMPONENT_POST_BUILD_ACTION = \
	(cd $(COMPONENT_DIR)/$(COMPONENT_SRC_1); \
	$(GMAKE) prefix=$(CONFIGURE_PREFIX) DESTDIR=$(PROTO_DIR) install)

# Always show the build and link lines for easier debugging.
COMPONENT_BUILD_ARGS += V=1

REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += image/library/openjpeg2
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
