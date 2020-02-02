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
# Copyright 2015 Ken Mays
#

X11_CATEGORY=DRIVER
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= xf86-video-r128
COMPONENT_VERSION= 6.10.2
COMPONENT_REVISION= 3
COMPONENT_FMRI= x11/server/xorg/driver/xorg-video-r128
COMPONENT_SUMMARY= xf86-video-r128 - ATI Rage 128 video driver for the Xorg X server
COMPONENT_ARCHIVE_HASH= \
  sha256:84da21517f3af7617fdf341e84ccb22444d6cdab1647e4808fa631528b9a77de

include $(WS_MAKE_RULES)/common.mk

LD_OPTIONS = \
        -L$(X11_SERVERMODS_DIR) -R$(X11_SERVERMODS_DIR) \
        -lint10 -lpciaccess -lfb -lpixman-1 -lvbe -lfbdevhw -lvgahw

# - Disable DRI since the kernel module isn't ported
CONFIGURE_OPTIONS += --disable-dri

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += system/header/header-drm

# Auto-generated dependencies
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/server/xorg
