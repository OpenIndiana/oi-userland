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

COMPONENT_NAME= xf86-input-keyboard
COMPONENT_VERSION= 1.9.0
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= \
  xf86-input-keyboard - Keyboard input driver for the Xorg X server
COMPONENT_FMRI = x11/server/xorg/driver/xorg-input-keyboard
COMPONENT_CLASSIFICATION= Drivers/Other Peripherals
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/driver/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:f7c900f21752683402992b288d5a2826de7a6c0c0abac2aadd7e8a409e170388
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && \
                          libtoolize --automake --copy --force && \
                          aclocal && \
                          autoheader && \
                          automake -a -f -c &&\
                          autoconf )

# Build dependencies
REQUIRED_PACKAGES += system/header/header-usb
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += x11/server/xorg

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
