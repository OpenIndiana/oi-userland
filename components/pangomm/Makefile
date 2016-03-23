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
# Copyright 2016 Till Wegmueller
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= pangomm

COMPONENT_VERSION= 2.36.0
COMPONENT_REVISION=1
COMPONENT_SUMMARY= pangomm - C++ Wrapper for the pango Library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:a8d96952c708d7726bed260d693cece554f8f00e48b97cccfbf4f5690b6821f0
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/pangomm/2.36/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gtkmm.org/
COMPONENT_LICENSE= LGPLv2
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_FMRI = library/desktop/c++/$(COMPONENT_NAME)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS += --sysconfdir=/etc

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
