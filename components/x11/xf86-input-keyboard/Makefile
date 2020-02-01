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

X11_CATEGORY=DRIVER
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= xf86-input-keyboard
COMPONENT_VERSION= 1.9.0
COMPONENT_REVISION= 3
COMPONENT_FMRI= x11/server/xorg/driver/xorg-input-keyboard
COMPONENT_SUMMARY= \
  xf86-input-keyboard - Keyboard input driver for the Xorg X server
COMPONENT_ARCHIVE_HASH= \
  sha256:f7c900f21752683402992b288d5a2826de7a6c0c0abac2aadd7e8a409e170388

include $(WS_MAKE_RULES)/common.mk

# Build dependencies
REQUIRED_PACKAGES += system/header/header-usb
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += x11/server/xorg

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
