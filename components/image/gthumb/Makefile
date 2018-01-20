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
# Copyright 2017 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gthumb
# Later versions use symbolic icons
COMPONENT_VERSION=	3.2.9.1
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/gthumb
COMPONENT_SUMMARY=	GNOME image organizer (gthumb)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:eda012f410fc3c45aafab727a81d484857d83e51f69febdfe76a44d2b5965f01
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/3.2/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	image/viewer/gthumb
COMPONENT_CLASSIFICATION=	Applications/Graphics and Imaging
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -fi)

CFLAGS   += -std=gnu89 -D_XOPEN_SOURCE=500
CPPFLAGS += -I/usr/include/lcms2

# Use default libjpeg
CPPFLAGS += $(JPEG_CPPFLAGS)
CFLAGS += $(JPEG_CFLAGS)
LDFLAGS += $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS+=	--enable-exiv2
CONFIGURE_OPTIONS+=	--enable-jpeg
CONFIGURE_OPTIONS+=	--enable-tiff
CONFIGURE_OPTIONS+=	--enable-gstreamer
CONFIGURE_OPTIONS+=	--enable-libwebp
CONFIGURE_OPTIONS+=	--enable-librsvg

CONFIGURE_ENV+= CPPFLAGS="$(CPPFLAGS)"

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/cd-burning/brasero
REQUIRED_PACKAGES += image/library/exiv2
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/clutter
REQUIRED_PACKAGES += library/desktop/clutter/clutter-gtk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/cogl
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
REQUIRED_PACKAGES += system/library/math
