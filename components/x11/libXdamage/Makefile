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

X11_CATEGORY=LIB
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=    libXdamage
COMPONENT_VERSION= 1.1.5
COMPONENT_FMRI=    x11/library/libxdamage
COMPONENT_SUMMARY= libXdamage - X Damage extension library 
COMPONENT_ARCHIVE_HASH= \
  sha256:b734068643cac3b5f3d2c8279dd366b5bf28c7219d9e9d8717e1383995e0ea45

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared

LD_OPTIONS += -M$(COMPONENT_DIR)/mapfile-vers

# Build dependencies
REQUIRED_PACKAGES += x11/library/libxfixes

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
