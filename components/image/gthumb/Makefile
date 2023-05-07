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
# Copyright 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gthumb
# Later versions use symbolic icons
COMPONENT_VERSION=      3.6.2
COMPONENT_REVISION=     6
COMPONENT_SUMMARY=      GNOME image organizer (gthumb)
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Apps/gthumb
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:c9bf6bb7502659f5e990069527584bb96193f7f5f9492f0bf5f65828f5024b66
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/3.6/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         image/viewer/gthumb
COMPONENT_CLASSIFICATION=Applications/Graphics and Imaging
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -fi )

# For ansidecl.h
CPPFLAGS += -I/usr/gnu/include
# For LCMS2 detection
CPPFLAGS += -I/usr/include/lcms2

# Use default libjpeg
CPPFLAGS += $(JPEG_CPPFLAGS)
CFLAGS += $(JPEG_CFLAGS)
LDFLAGS += $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=/usr/lib
CONFIGURE_OPTIONS += --enable-exiv2
CONFIGURE_OPTIONS += --enable-jpeg
CONFIGURE_OPTIONS += --enable-tiff
CONFIGURE_OPTIONS += --enable-gstreamer
CONFIGURE_OPTIONS += --enable-libwebp
CONFIGURE_OPTIONS += --enable-librsvg

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# Build dependencies
REQUIRED_PACKAGES += library/gnome/yelp-tools
REQUIRED_PACKAGES += text/itstool

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += desktop/cd-burning/brasero
REQUIRED_PACKAGES += image/library/exiv2
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libraw
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/webkitgtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
