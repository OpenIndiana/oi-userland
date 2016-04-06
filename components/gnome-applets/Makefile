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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= gnome-applets
COMPONENT_VERSION= 2.32.1.1
COMPONENT_REVISION= 1
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
