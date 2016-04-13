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

COMPONENT_NAME= gphoto2
COMPONENT_VERSION= 2.4.14
COMPONENT_SUMMARY= Digital camera utility
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:8754cdf1ee8eb3ef636c05d052646957d3f087892ed867543ab9180a3bbaa123
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/gphoto/files/gphoto/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL = http://www.gphoto.org
COMPONENT_CLASSIFICATION = Applications/Graphics and Imaging
COMPONENT_FMRI = desktop/gphoto2
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

build: $(BUILD_32)

install: $(INSTALL_32)

# test031 fails
test: $(TEST_32)
