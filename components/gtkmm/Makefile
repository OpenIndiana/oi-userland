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

COMPONENT_NAME= gtkmm

COMPONENT_VERSION= 2.24.4
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= gtkmm - C++ Wrapper for the Gtk+ Library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:443a2ff3fcb42a915609f1779000390c640a6d7fd19ad8816e6161053696f5ee
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/gtkmm/2.24/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gtkmm.org/
COMPONENT_LICENSE= LGPLv2
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_FMRI = library/desktop/c++/$(COMPONENT_NAME)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# test_shutdown_stress fails 
test: $(TEST_32_and_64)
