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
# Copyright 2015 Aurelien Larcher
#

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           xrdb
COMPONENT_VERSION=        1.2.0
COMPONENT_SUMMARY=        xrdb - X server resource database utility
COMPONENT_FMRI=           x11/xrdb
COMPONENT_ARCHIVE_HASH= \
  sha256:f23a65cfa1f7126040d68b6cf1e4567523edac10f8dc06f23d840d330c7c6946

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+= --with-cpp=/usr/lib/cpp

CPPFLAGS+= -DPATHETICCPP

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmuu
