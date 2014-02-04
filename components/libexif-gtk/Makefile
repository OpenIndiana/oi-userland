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

COMPONENT_NAME= libexif-gtk

COMPONENT_VERSION= 0.4.0
COMPONENT_SUMMARY= GTK widgets for viewing EXIF information
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:fd36a5b243f12a1ba31342acf7547491fe22f5409f3bf39ec1a11239316f3011
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/libexif/files/libexif-gtk/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL = http://sourceforge.net/projects/libexif

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

gcc_OPT = -O2

CONFIGURE_OPTIONS += --disable-static

COMPONENT_INSTALL_TARGETS = install-strip

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)
