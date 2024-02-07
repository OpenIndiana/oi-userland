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
# Copyright 2023 Friedrich Kink
#

BUILD_STYLE=		meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gthumb
COMPONENT_VERSION=      3.12.4
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=      GNOME image organizer (gthumb)
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Apps/gthumb
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:add693ac0aeb9a30d829ba03a06208289d3f6868dc3b02573549e88190c794e8
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/3.12/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         image/viewer/gthumb
COMPONENT_CLASSIFICATION=Applications/Graphics and Imaging
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# For LCMS2 detection
CPPFLAGS += -I/usr/include/lcms2

CPPFLAGS += $(JPEG_CPPFLAGS)
CFLAGS += $(JPEG_CFLAGS)
LDFLAGS += $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=/usr/lib

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

COMPONENT_TEST_TRANSFORMS = \
        '-e "s/OK.*$$/OK/" ' \
        '-e "/^Full log written to/d" '

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
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/clutter
REQUIRED_PACKAGES += library/desktop/clutter/clutter-gtk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libchamplain
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
REQUIRED_PACKAGES += x11/library/libx11
