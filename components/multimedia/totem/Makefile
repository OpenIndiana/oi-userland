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
# Copyright 2020 Alexander Pyhalov
#

BUILD_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= totem
# Later versions require clutter-gtk-1.0
COMPONENT_VERSION= 3.0.1
COMPONENT_REVISION= 6
COMPONENT_COMMIT= bfc537c4cdcd51e747611a37fc3583d26e4d634f
COMPONENT_SUMMARY= Totem Multimedia Player
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:e97fc66d925ff4bfcc6422486fc58c86fbdbccf2a56ec2e031e916104160a0fc
COMPONENT_ARCHIVE_URL= \
  https://github.com/OpenIndiana/totem/archive/$(COMPONENT_COMMIT).tar.gz
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_FMRI = gnome/media/totem
COMPONENT_CLASSIFICATION = Applications/Sound and Video
COMPONENT_LICENSE = GPLv2 with plugins exception
COMPONENT_LICENSE_FILE = COPYING

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = (cd $(@D) &&\
			intltoolize &&\
			gtkdocize &&\
			gnome-doc-prepare &&\
			autoreconf -fi)

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --localstatedir=/var/lib
CONFIGURE_OPTIONS+= --libexecdir=/usr/lib
CONFIGURE_OPTIONS+= --disable-browser-plugins
CONFIGURE_OPTIONS+= --disable-nautilus
CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --with-pic

CONFIGURE_OPTIONS+= --with-plugins='\
		brasero-disc-recorder \
		chapters \
		dbusservice \
		gromit \
		im-status \
		media-player-keys \
		ontop \
		opensubtitles \
		properties \
		pythonconsole \
		samplepython \
		sample-vala \
		screensaver \
		screenshot \
		sidebar-test \
		skipto \
		thumbnail'

CONFIGURE_ENV    += PYTHON=$(PYTHON.3.5.64)

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

REQUIRED_PACKAGES += developer/gnome/gnome-doc-utils

REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libpeas
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/media-player/totem-pl-parser
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxtst
REQUIRED_PACKAGES += x11/library/libxxf86vm
