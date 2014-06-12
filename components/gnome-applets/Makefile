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
COMPONENT_VERSION= 2.30.0
COMPONENT_SUMMARY= GNOME panel applets
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:41489fbb1f8352a306cde6676dfaf1e497bfbca960454f7251c4fd92920bba5d
COMPONENT_ARCHIVE_URL= \
  http://download.gnome.org/sources/$(COMPONENT_NAME)/2.30/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

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
CONFIGURE_OPTIONS+= --enable-mixer-applet
CONFIGURE_OPTIONS+= --disable-networkmanager

COMPONENT_INSTALL_ENV += GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

build: $(BUILD_32)

install: $(INSTALL_32)
