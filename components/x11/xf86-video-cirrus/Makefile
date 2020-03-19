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
# Copyright 2017 Michal Nowak
#

X11_CATEGORY=DRIVER
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= xf86-video-cirrus
COMPONENT_VERSION= 1.5.3
COMPONENT_REVISION= 3
COMPONENT_FMRI= x11/server/xorg/driver/xorg-video-cirrus
COMPONENT_SUMMARY= xf86-video-cirrus - Cirrus Logic video driver for the Xorg X server
COMPONENT_ARCHIVE_HASH= \
  sha256:edc87b20a55259126b5239b5c1ef913419eab7ded0ed12ae9ae989460d7351ab

include $(WS_MAKE_RULES)/common.mk

# Paths to find libraries/modules to link with 

LD_OPTIONS= \
        -L$(X11_SERVERMODS_DIR) -R$(X11_SERVERMODS_DIR) \
        -L$(X11_SERVERLIBS_DIR) -R$(X11_SERVERLIBS_DIR) 

# Build dependencies
REQUIRED_PACKAGES += developer/build/autoconf/xorg-macros
REQUIRED_PACKAGES += developer/build/pkg-config
REQUIRED_PACKAGES += x11/header/x11-protocols

# Auto-generated dependencies
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/server/xorg
