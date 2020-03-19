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

COMPONENT_NAME= xf86-video-dummy
COMPONENT_VERSION= 0.3.8
COMPONENT_REVISION= 3
COMPONENT_FMRI= x11/server/xorg/driver/xorg-video-dummy
COMPONENT_SUMMARY= \
  xf86-video-dummy - virtual/offscreen frame buffer driver for the Xorg X server
COMPONENT_ARCHIVE_HASH= \
  sha256:3712bb869307233491e4c570732d6073c0dc3d99adfdb9977396a3fdf84e95b9

include $(WS_MAKE_RULES)/common.mk

# Paths to find libraries/modules to link with 

LD_OPTIONS= \
        -L$(X11_SERVERMODS_DIR) -R$(X11_SERVERMODS_DIR) \
        -L$(X11_SERVERLIBS_DIR) -R$(X11_SERVERLIBS_DIR) \
        -lfb

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/server/xorg
