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

COMPONENT_NAME= xf86-input-mouse
COMPONENT_VERSION= 1.9.4
COMPONENT_SUMMARY= xf86-input-mouse - Mouse input driver for the Xorg X server
COMPONENT_FMRI= x11/server/xorg/driver/xorg-input-mouse
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:7f6f8551fc238abdddcf9f38906564c1f8c7dacb0ad947cfc110487aefbd8d4c

include $(WS_MAKE_RULES)/common.mk

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
