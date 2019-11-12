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

BUILD_BITS = 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= xf86-input-vmmouse
COMPONENT_VERSION= 13.1.0
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= xf86-input-vmmouse - VMWare guest mouse input driver for the Xorg X server
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:0af558957ac1be1b2863712c2475de8f4d7f14921fd01ded2e2fde4921b19319
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/driver/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org
COMPONENT_CLASSIFICATION= Drivers/Other Peripherals
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_FMRI = x11/server/xorg/driver/xorg-input-vmmouse

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

HAL_CALLOUTS_DIR.32=/usr/lib/hal
HAL_CALLOUTS_DIR.64=/usr/lib/hal/$(MACH64)

CONFIGURE_BINDIR.32=/usr/lib/xorg
CONFIGURE_BINDIR.64=/usr/lib/xorg/$(MACH64)

CFLAGS+= -std=gnu99

CONFIGURE_OPTIONS += --with-hal-bin-dir=/usr/sbin
CONFIGURE_OPTIONS += --with-hal-callouts-dir=$(HAL_CALLOUTS_DIR.$(BITS))
CONFIGURE_OPTIONS += --with-hal-fdi-dir=/etc/hal/fdi/policy/10osvendor
CONFIGURE_OPTIONS += --without-libudev
CONFIGURE_OPTIONS += --with-udev-rules-dir=no

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libpthread-stubs
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libx11
