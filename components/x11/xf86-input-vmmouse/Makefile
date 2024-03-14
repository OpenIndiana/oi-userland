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

COMPONENT_NAME= xf86-input-vmmouse
COMPONENT_VERSION= 13.2.0
COMPONENT_SUMMARY= xf86-input-vmmouse - VMWare guest mouse input driver for the Xorg X server
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:56f077580ab8f02e2f40358c5c46b0ae3e1828fc77744526b24adf1ceea339b8
COMPONENT_FMRI= x11/server/xorg/driver/xorg-input-vmmouse

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_BINDIR.32=$(XORG_LIBDIR)
CONFIGURE_BINDIR.64=$(XORG_LIBDIR)

CFLAGS+= -std=gnu99

CONFIGURE_OPTIONS += --with-hal-bin-dir=/usr/sbin
CONFIGURE_OPTIONS += --with-hal-callouts-dir=/usr/lib/hal
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
# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
