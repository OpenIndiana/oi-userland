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

COMPONENT_NAME= xf86-input-void
COMPONENT_VERSION= 1.4.1
COMPONENT_REVISION= 2
COMPONENT_FMRI= x11/server/xorg/driver/xorg-input-void
COMPONENT_SUMMARY= xf86-input-void - null input driver for Xorg server
COMPONENT_ARCHIVE_HASH= \
  sha256:f96e4f0a622821bf43a74bd419f2a18423343996c9d243c7e1430ba2d142339c

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += system/library
