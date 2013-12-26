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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= xrx

COMPONENT_VERSION= 1.0.4
COMPONENT_SUMMARY= RX: X Remote eXecution (aka Xweb or Broadway)
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:b5eb5ecae105ed4d3b2c91193a1c2ef9fe51b1145190541a59f92645899763a4
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/app/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.broadwayinfo.com/

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_LIBDIR.32=/usr/lib/firefox/plugins

CONFIGURE_OPTIONS+= PLUGIN_CFLAGS='-I$$(COMPONENT_SRC)/plugin/include'
CONFIGURE_OPTIONS+= --enable-shared=yes
CONFIGURE_OPTIONS+= --enable-static=no

build: $(BUILD_32)

install: $(INSTALL_32)
