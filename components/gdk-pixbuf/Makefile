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

COMPONENT_NAME= gdk-pixbuf

COMPONENT_VERSION= 2.24.1
COMPONENT_SUMMARY= GNOME gdk-pixbuf
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:da7a3f00db360913716368e19e336402755cafa93769f3cfa28a969303e4bee1
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.24/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://cairographics.org

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

gcc_OPT = -O2

COMPONENT_PREP_ACTION =        ( cd $(@D) && autoconf )

CONFIGURE_OPTIONS.32 += --sysconfdir=/etc
CONFIGURE_OPTIONS.64 += --sysconfdir=/etc/$(MACH64)
CONFIGURE_OPTIONS += --with-x11

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_POST_INSTALL_ACTION.32 = ( LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib \
	$(PROTO_DIR)/usr/bin/gdk-pixbuf-query-loaders \
	   $(PROTO_DIR)/usr/lib/gdk-pixbuf-2.0/*/loaders/*.so	| sed -e "s:$(PROTO_DIR)::" \
	   > $(PROTO_DIR)/usr/lib/gdk-pixbuf-2.0/2.10.0/loaders.cache )

COMPONENT_POST_INSTALL_ACTION.64 = ( LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib/$(MACH64) \
	$(PROTO_DIR)/usr/bin/$(MACH64)/gdk-pixbuf-query-loaders \
	   $(PROTO_DIR)/usr/lib/$(MACH64)/gdk-pixbuf-2.0/*/loaders/*.so	| sed -e "s:$(PROTO_DIR)::" \
	   > $(PROTO_DIR)/usr/lib/$(MACH64)/gdk-pixbuf-2.0/2.10.0/loaders.cache )

COMPONENT_POST_INSTALL_ACTION=$(COMPONENT_POST_INSTALL_ACTION.$(BITS))

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
