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
# Copyright 2024 Geoff Weiss
#

include ../../../make-rules/shared-macros.mk
ENV= /usr/bin/env

COMPONENT_NAME=		gtk4
COMPONENT_VERSION=	4.10.5
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	GTK+4 - GIMP Toolkit Library for creation of graphical user interfaces
COMPONENT_SRC=		gtk-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:9bd5e437e41d48e3d6a224c336b0fd3fd490036dceb8956ed74b956369af609b
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/gtk/4.10/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.gtk.org/
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_FMRI=		library/desktop/gtk4

BUILD_STYLE=		meson

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Uses isinf, etc. only available in c99 and newer
CFLAGS.gcc += -std=gnu11

#needed to produce /usr/lib/amd64/girepository-1.0 files
CONFIGURE_OPTIONS += -Dintrospection=enabled

CONFIGURE_OPTIONS += -Dman-pages=true
# requires encumbered x264 support
CONFIGURE_OPTIONS += -Dmedia-gstreamer=disabled
CONFIGURE_OPTIONS += -Dwayland-backend=false

COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# Add missing rpaths 
COMPONENT_POST_INSTALL_ACTION  = \
   /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(JPEG_LIBDIR)"' $(PROTO_DIR)/usr/bin/gtk4-encode-symbolic-svg ; \
   /usr/bin/elfedit -e 'dyn:value -s  RPATH   "$(JPEG_LIBDIR)"' $(PROTO_DIR)/usr/bin/gtk4-encode-symbolic-svg ; \
   /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(JPEG_LIBDIR)"' $(PROTO_DIR)/usr/lib/amd64/libgtk-4.so.1.1000.5 ; \
   /usr/bin/elfedit -e 'dyn:value -s  RPATH   "$(JPEG_LIBDIR)"' $(PROTO_DIR)/usr/lib/amd64/libgtk-4.so.1.1000.5 ;

COMPONENT_TEST_TRANSFORMS += \
        '-e "s/seed:[0-9]*/seed:/"'
# get rid of the timestamps from the test results
COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9]*[0-9].[0-9][0-9]s//" '
COMPONENT_TEST_TRANSFORMS += '-e "s/OK      [0-9]//" '
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/OK/p" '
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH64).master

# Build dependencies
REQUIRED_PACKAGES += library/python/docutils

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/graphene
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libepoxy
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
