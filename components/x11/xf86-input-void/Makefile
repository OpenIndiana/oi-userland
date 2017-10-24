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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= xf86-input-void
COMPONENT_VERSION= 1.4.1
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= xf86-input-void - null input driver for Xorg server
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org
COMPONENT_FMRI = x11/server/xorg/driver/xorg-input-void
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/driver/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:f96e4f0a622821bf43a74bd419f2a18423343996c9d243c7e1430ba2d142339c
COMPONENT_CLASSIFICATION= Drivers/Other Peripherals
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += system/library
