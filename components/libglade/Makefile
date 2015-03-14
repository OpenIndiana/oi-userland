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
# Copyright 2015 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= libglade
COMPONENT_VERSION= 2.6.4
COMPONENT_SUMMARY= GNOME library for loading GLADE interfaces at runtime
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:64361e7647839d36ed8336d992fd210d3e8139882269bed47dc4674980165dec
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.6/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_LICENSE = LGPLv2
COMPONENT_FMRI = library/desktop/libglade
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Libraries

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CFLAGS += -D__EXTENSIONS__

CONFIGURE_OPTIONS += --sysconfdir=/etc

CONFIGURE_ENV+= PYTHON=$(PYTHON)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
