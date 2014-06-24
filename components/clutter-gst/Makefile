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

COMPONENT_NAME= clutter-gst
COMPONENT_VERSION= 1.6.0
COMPONENT_SUMMARY= gstreamer integration library for clutter
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:abc879cdd562f1640a825131405f4327a427bfe65b805ebc25d0c78909c8c622
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/mirror/gnome.org/sources/$(COMPONENT_NAME)/1.6/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.clutter-project.org/

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH = /usr/gnu/bin:/usr/bin

CFLAGS += -I/usr/X11/include
LDFLAGS += -lgdk_pixbuf-2.0

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/$(MACH64)

# Tell g-ir-scanner about compiler
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
