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
# Copyright 2015-2017 Aurelien Larcher
# Copyright 2020 Michal Nowak
# Copyright 2021 Andreas Wacknitz
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		inkscape
COMPONENT_VERSION=	1.2.2
# COMPONENT_ITEM_NO is part of the download path
# (find it on https://inkscape.org/release/inkscape-1.2.1/source/archive/xz/dl/ under "click here")
# eg. https://inkscape.org/gallery/item/34673/inkscape-1.2.1.tar.xz
COMPONENT_ITEM_NO=	37360
# COMPONENT_DATE and COMPONENT_HASH are part of the resulting source path:
COMPONENT_DATE=		2022-12-01
COMPONENT_HASH=		b0a8486541
COMPONENT_SUMMARY=	Opensource professional vector graphics editor
COMPONENT_PROJECT_URL=	https://www.inkscape.org/
COMPONENT_SRC_BASE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_SRC=		$(COMPONENT_SRC_BASE)_$(COMPONENT_DATE)_$(COMPONENT_HASH)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC_BASE).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:a0c7fd0d03c0a21535e648ef301dcf80dd7cfc1f3545e51065fbf1ba3ee8a5c4
COMPONENT_ARCHIVE_URL=	https://inkscape.org/gallery/item/$(COMPONENT_ITEM_NO)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		image/editor/inkscape
COMPONENT_CLASSIFICATION=	Applications/Graphics and Imaging
COMPONENT_LICENSE=	GPLv2, GPLv3
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

LDFLAGS += $(JPEG_LDFLAGS)

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DCMAKE_ENABLE_LCMS=ON
CMAKE_OPTIONS += -DLCMS2_INCLUDE_DIR=$(USRINCDIR)/lcms2
CMAKE_OPTIONS += -DLCMS2_LIBRARY=$(USRLIBDIR.$(BITS))/liblcms2.so
CMAKE_OPTIONS += -DCMAKE_ENABLE_LCMS=ON
CMAKE_OPTIONS += -DCMAKE_ENABLE_POPPLER_CAIRO=ON
CMAKE_OPTIONS += -DWITH_IMAGE_MAGICK=ON
CMAKE_OPTIONS += -DWITH_LIBCDR=ON
CMAKE_OPTIONS += -DWITH_LIBVISIO=ON
CMAKE_OPTIONS += -DWITH_LIBWPG=ON
CMAKE_OPTIONS += -DCMAKE_ENABLE_BINRELOC=OFF
CMAKE_OPTIONS += -DWITH_GNOME_VFS=ON
CMAKE_OPTIONS += -DWITH_OPENMP=ON
CMAKE_OPTIONS += -DJPEG_INCLUDE_DIR=$(JPEG_INCDIR)
CMAKE_OPTIONS += -DJPEG_LIBRARY=$(JPEG_LIBDIR)/libjpeg.so

COMPONENT_TEST_TRANSFORMS += \
	' -e "s/[0-9]*\.[0-9]* sec//" ' \
	' -n ' \
	' -e "/passed/p" ' \
	' -e "/Passed/p" ' \
	' -e "/Failed/p" ' \
	' -e "/FAILED/p" ' \
	' -e "/Skipped/p" ' \
	' -e "/not run/p" ' \
	' -e "/Not Run/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += developer/gsl
REQUIRED_PACKAGES += image/imagemagick
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/potrace
REQUIRED_PACKAGES += library/c++/glibmm
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/c++/libcdr
REQUIRED_PACKAGES += library/c++/librevenge
REQUIRED_PACKAGES += library/c++/libvisio
REQUIRED_PACKAGES += library/c++/libwpg
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/c++/atkmm
REQUIRED_PACKAGES += library/desktop/c++/cairomm
REQUIRED_PACKAGES += library/desktop/c++/gtkmm3
REQUIRED_PACKAGES += library/desktop/c++/pangomm
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gspell
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/gc
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/lib2geom
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/boost
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
