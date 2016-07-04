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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= rhythmbox
COMPONENT_VERSION= 0.13.3
COMPONENT_REVISION= 3
COMPONENT_SUMMARY= Rhythmbox Multimedia Player
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:ad6532864bb4df30f1014ec81ddc0d2d3f69241235627f46abe5578cf629052a
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/0.13/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PYTHON_VERSION=2.7

CXXFLAGS+= -DMOZ_DEFAULT_TOOLKIT=\"cairo-gtk2\"
CXXFLAGS+= -std=gnu++0x
CFLAGS += -I/usr/include/check

COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D) && cd $(@D) &&\
		intltoolize --copy --force --automake &&\
		aclocal -I ./macros &&\
		autoheader &&\
		automake -a -c -f&&\
		autoconf)

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --disable-browser-plugin
CONFIGURE_OPTIONS+= --enable-gstreamer
CONFIGURE_OPTIONS+= --libexecdir=/usr/lib
CONFIGURE_OPTIONS+= --localstatedir=/var/lib
CONFIGURE_OPTIONS+= --with-mtp=no
CONFIGURE_ENV    += XGETTEXT=/usr/gnu/bin/xgettext
CONFIGURE_ENV    += MSGFMT=/usr/gnu/bin/msgfmt
CONFIGURE_ENV    += PYTHON=$(PYTHON)
COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

build: $(BUILD_32)

install: $(INSTALL_32)

REQUIRED_PACKAGES += desktop/cd-burning/brasero
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += gnome/media/gnome-media
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/webkitgtk
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/media-player/totem-pl-parser
REQUIRED_PACKAGES += library/musicbrainz/libmusicbrainz-3
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
