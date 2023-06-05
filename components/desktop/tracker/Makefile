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
# Copyright 2017 Alexander Pyhalov
# Copyright 2018 Michal Nowak
# Copyright 2019 Tim Mooney
#

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         tracker
COMPONENT_VERSION=      1.8.3
COMPONENT_REVISION=     12
COMPONENT_SUMMARY=      Desktop search tool
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:9bbf8c8525b3a1496716a350bc50ba06af5e880a4386506ca3e45d6779065c42
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/1.8/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://gitlab.gnome.org/GNOME/tracker
COMPONENT_FMRI=         library/desktop/search/tracker
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_LICENSE=      GPLv2,LGPLv2.1

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CFLAGS += -std=gnu89 -D_XOPEN_SOURCE=500 -D__EXTENSIONS__

# Use default libjpeg
CPPFLAGS += $(JPEG_CPPFLAGS)
CFLAGS += $(JPEG_CFLAGS)
LDFLAGS += $(JPEG_LDFLAGS)
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

COMPONENT_PREP_ACTION= ( cd $(@D) && autoreconf -fi)

COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=/usr/bin
CONFIGURE_OPTIONS += --disable-libstemmer
CONFIGURE_OPTIONS += --disable-maemo
CONFIGURE_OPTIONS += --disable-schemas-compile
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-upower
CONFIGURE_OPTIONS += --enable-artwork
CONFIGURE_OPTIONS += --enable-cfg-man-pages
CONFIGURE_OPTIONS += --enable-dvi
CONFIGURE_OPTIONS += --enable-generic-media-extractor=gstreamer
# Evolution miner is broken (crashes on startup)
CONFIGURE_OPTIONS += --disable-miner-evolution
# Disabled for now because of errors
CONFIGURE_OPTIONS += --disable-gtk-doc
CONFIGURE_OPTIONS += --enable-hal
CONFIGURE_OPTIONS += --enable-icon
CONFIGURE_OPTIONS += --enable-icu-charset-detection
# Required for other components.
CONFIGURE_OPTIONS.64 += --enable-introspection
CONFIGURE_OPTIONS += --enable-journal
CONFIGURE_OPTIONS += --enable-libexif
CONFIGURE_OPTIONS += --enable-libflac
CONFIGURE_OPTIONS += --enable-libjpeg
CONFIGURE_OPTIONS += --enable-libpng
CONFIGURE_OPTIONS += --enable-libtiff
CONFIGURE_OPTIONS += --enable-libvorbis
CONFIGURE_OPTIONS += --enable-libxml2
CONFIGURE_OPTIONS += --enable-miner-apps
CONFIGURE_OPTIONS += --enable-miner-fs
CONFIGURE_OPTIONS += --disable-miner-firefox
CONFIGURE_OPTIONS += --disable-miner-thunderbird
CONFIGURE_OPTIONS += --enable-miner-user-guides
CONFIGURE_OPTIONS += --enable-mp3
CONFIGURE_OPTIONS += --disable-nautilus-extension
CONFIGURE_OPTIONS += --enable-playlist
CONFIGURE_OPTIONS += --enable-poppler
CONFIGURE_OPTIONS += --enable-ps
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-taglib
CONFIGURE_OPTIONS += --enable-text
CONFIGURE_OPTIONS += --enable-tracker-fts
CONFIGURE_OPTIONS += --enable-tracker-needle
CONFIGURE_OPTIONS += --enable-tracker-preferences
CONFIGURE_OPTIONS += --enable-tracker-writeback
CONFIGURE_OPTIONS += --disable-miner-firefox
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-unicode-support=libicu
CONFIGURE_OPTIONS += --libexecdir=$(USRLIBDIR)


CONFIGURE_ENV    += PERL=$(PERL)

COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# Build dependencies
REQUIRED_PACKAGES += utility/bash-completion
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/audio/taglib
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libgsf
REQUIRED_PACKAGES += library/giflib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/media-player/totem-pl-parser
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
