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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME= gnome-applets
COMPONENT_VERSION= 2.32.1.1
COMPONENT_REVISION= 3
COMPONENT_SUMMARY= GNOME panel applets
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:2b92fe4b3062dfbe264f45472b4db3a27d1e69e13260d37da9fb36b2cbd40327
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.gnome.org/pub/gnome/sources/$(COMPONENT_NAME)/2.32/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
                                        libtoolize --automake --copy --force && \
					aclocal -I./m4 && \
                                        autoheader && \
					automake  -Wno-portability -a -f -c &&\
					autoconf )

CONFIGURE_ENV	+= PYTHON=$(PYTHON)
CONFIGURE_ENV	+= am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV	+= am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV	+= LIBGWEATHER_LIBS="-lgweather -lm"
CONFIGURE_ENV	+= LIBS="-lm"

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --libexecdir=/usr/lib
CONFIGURE_OPTIONS+= --with-gstreamer=0.10
CONFIGURE_OPTIONS+= --enable-stickynotes
CONFIGURE_OPTIONS+= --disable-scrollkeeper
CONFIGURE_OPTIONS+= --disable-mixer-applet
CONFIGURE_OPTIONS+= --disable-networkmanager

COMPONENT_INSTALL_ENV += GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

build: $(BUILD_32)

install: $(INSTALL_32)

REQUIRED_PACKAGES += desktop/character-map/gucharmap
REQUIRED_PACKAGES += developer/gnome/gnome-doc-utils
REQUIRED_PACKAGES += gnome/applet/deskbar-applet
REQUIRED_PACKAGES += gnome/applet/gnome-netstatus
REQUIRED_PACKAGES += gnome/applet/quick-lounge-applet
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += gnome/gnome-panel
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gnome-desktop
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libgweather
REQUIRED_PACKAGES += library/desktop/libwnck
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libbonobo
REQUIRED_PACKAGES += library/libgtop
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/python/pygobject-27
REQUIRED_PACKAGES += library/python/pygobject
REQUIRED_PACKAGES += library/python/pygtk2-27
REQUIRED_PACKAGES += library/python/pygtk2
REQUIRED_PACKAGES += library/python/python-gnome-desktop-27
REQUIRED_PACKAGES += library/python/python-gnome-desktop
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
