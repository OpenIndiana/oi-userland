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
# Copyright 2015-2021 Aurelien Larcher
#

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           xrdb
COMPONENT_VERSION=        1.2.2
COMPONENT_SUMMARY=        xrdb - X server resource database utility
COMPONENT_ARCHIVE=        $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH=   sha256:31f5fcab231b38f255b00b066cf7ea3b496df712c9eb2d0d50c670b63e5033f4
COMPONENT_FMRI=           x11/xrdb
COMPONENT_LICENSE_FILE=   COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+= --with-cpp=/usr/lib/cpp

CPPFLAGS+= -DPATHETICCPP

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmuu
