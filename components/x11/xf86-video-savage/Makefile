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

COMPONENT_NAME= xf86-video-savage
COMPONENT_VERSION= 2.3.9
COMPONENT_REVISION= 3
COMPONENT_FMRI= x11/server/xorg/driver/xorg-video-savage
COMPONENT_SUMMARY= xf86-video-savage - S3 Savage video driver for the Xorg X server
COMPONENT_ARCHIVE_HASH= \
  sha256:2c93c4db1f71e725dda0caee5821253129d4b52d7aa0fd720593e7769bceec86

include $(WS_MAKE_RULES)/common.mk

LD_OPTIONS= -M$(COMPONENT_DIR)/mapfile.externs \
        -L$(X11_SERVERMODS_DIR) -R$(X11_SERVERMODS_DIR) \
        -L$(X11_SERVERLIBS_DIR) -R$(X11_SERVERLIBS_DIR) \
        -lexa -lfb -lint10 -lpciaccess -lshadowfb -lXfont -lvbe -lvgahw -lm

# - Disable DRI since the kernel module isn't ported
CONFIGURE_OPTIONS += --disable-dri

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += system/header/header-drm

# Auto-generated dependencies
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libxfont
REQUIRED_PACKAGES += x11/server/xorg
