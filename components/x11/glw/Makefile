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
BUILD_BITS=32_and_64
COMPONENT_X11_DEFAULTS=no

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= glw
COMPONENT_VERSION= 8.0.0
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= libglw part of the Mesa 3-D Graphics Library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:2da1d06e825f073dcbad264aec7b45c649100e5bcde688ac3035b34c8dbc8597
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.freedesktop.org/pub/mesa/glw/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mesa3d.org/

include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL=0

LDFLAGS= -L$(X11_SERVERLIBS_DIR) -R$(X11_SERVERLIBS_DIR)

# 2023-07-14 Stephan Althaus - motif deactivated because of missing sources/package in the oi-userland tree
#CONFIGURE_OPTIONS += --enable-motif
REQUIRED_PACKAGES += developer/build/autoconf/xorg-macros
REQUIRED_PACKAGES += x11/header/x11-protocols

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/toolkit/libxt
