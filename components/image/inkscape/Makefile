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
# Copyright 2019 Michal Nowak
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		inkscape
COMPONENT_VERSION=	0.92.4
COMPONENT_REVISION=	1
COMPONENT_FMRI=		image/editor/inkscape
COMPONENT_CLASSIFICATION=	Applications/Graphics and Imaging
COMPONENT_SUMMARY=	Opensource professional vector graphics editor
COMPONENT_PROJECT_URL=	http://www.inkscape.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:57ec2da8177b36614a513e2822efd73af721e690f7ddc6bd0a5fbb1525b4515e
COMPONENT_ARCHIVE_URL=	https://media.inkscape.org/dl/resources/file/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

LDFLAGS+= $(JPEG_LDFLAGS)

CMAKE_OPTIONS+=  -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS+=  -DCMAKE_ENABLE_LCMS=ON
CMAKE_OPTIONS+=  -DLCMS2_INCLUDE_DIR=$(USRINCDIR)/lcms2
CMAKE_OPTIONS+=  -DLCMS2_LIBRARY=$(USRLIBDIR.$(BITS))/liblcms2.so
CMAKE_OPTIONS+=  -DCMAKE_ENABLE_LCMS=ON
CMAKE_OPTIONS+=  -DCMAKE_ENABLE_POPPLER_CAIRO=ON
CMAKE_OPTIONS+=  -DWITH_IMAGE_MAGICK=ON
CMAKE_OPTIONS+=  -DWITH_LIBCDR=ON
CMAKE_OPTIONS+=  -DWITH_LIBVISIO=ON
CMAKE_OPTIONS+=  -DWITH_LIBWPG=ON
CMAKE_OPTIONS+=  -DCMAKE_ENABLE_BINRELOC=OFF
CMAKE_OPTIONS+=  -DWITH_GNOME_VFS=ON
CMAKE_OPTIONS+=  -DWITH_OPENMP=ON
CMAKE_OPTIONS+=  -DJPEG_INCLUDE_DIR=$(JPEG_INCDIR)
CMAKE_OPTIONS+=  -DJPEG_LIBRARY=$(JPEG_LIBDIR)/libjpeg.so

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += developer/gsl
REQUIRED_PACKAGES += image/imagemagick
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/c++/glibmm
REQUIRED_PACKAGES += library/c++/libcdr
REQUIRED_PACKAGES += library/c++/librevenge
REQUIRED_PACKAGES += library/c++/libvisio
REQUIRED_PACKAGES += library/c++/libwpg
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/c++/atkmm
REQUIRED_PACKAGES += library/desktop/c++/cairomm
REQUIRED_PACKAGES += library/desktop/c++/gtkmm
REQUIRED_PACKAGES += library/desktop/c++/pangomm
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtkspell
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/gc
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-vfs
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/popt
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/aspell
REQUIRED_PACKAGES += x11/library/libx11
