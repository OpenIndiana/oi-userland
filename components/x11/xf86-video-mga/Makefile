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

COMPONENT_NAME= xf86-video-mga
COMPONENT_VERSION= 1.6.5
COMPONENT_REVISION= 3
COMPONENT_FMRI= x11/server/xorg/driver/xorg-video-mga
COMPONENT_SUMMARY= xf86-video-mga - Matrox MGA driver for the Xorg X server
COMPONENT_ARCHIVE_HASH= \
  sha256:b663cd8e6364f7c4e2637b9fcab9861d0e3971518c73b00d213f6545a1289422

include $(WS_MAKE_RULES)/common.mk

# Extra flags to link mga_drv.so, but not util/stormdwg binary with
DRIVER_LD_FLAGS = -L$(X11_SERVERMODS_DIR) -R$(X11_SERVERMODS_DIR)

# - Disable DRI since the kernel module isn't ported
CONFIGURE_OPTIONS += --disable-dri

CONFIGURE_OPTIONS += XORG_LIBS="$(DRIVER_LD_FLAGS)"

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += system/header/header-drm

# Auto-generated dependencies
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/server/xorg
