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

COMPONENT_NAME= xf86-input-acecad
COMPONENT_VERSION= 1.5.0
COMPONENT_REVISION= 3
COMPONENT_FMRI= x11/server/xorg/driver/xorg-input-acecad
COMPONENT_SUMMARY= xf86-input-acecad - Acecad Flair input driver for the Xorg X server
COMPONENT_ARCHIVE_HASH= \
  sha256:c3032f38a07b54772299ce8832e16109a685ee63eeefbb17cef9fe1dd100a448

include $(WS_MAKE_RULES)/common.mk

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += x11/server/xorg

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
