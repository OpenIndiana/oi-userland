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

COMPONENT_NAME= xf86-video-vmware
COMPONENT_VERSION= 13.4.0
COMPONENT_SUMMARY= xf86-video-vmware - VMWare driver for the Xorg X server
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:aed31ee5ed5ecc6e2226705383e7ad06f7602c1376a295305f376b17af3eb81a
COMPONENT_FMRI= x11/server/xorg/driver/xorg-video-vmware

include $(WS_MAKE_RULES)/common.mk

LD_OPTIONS= \
        -L$(X11_SERVERMODS_DIR) -R$(X11_SERVERMODS_DIR) \
        -lfb -lpixman-1 -lshadowfb -lvgahw -lpciaccess

CONFIGURE_ENV += with_xorg_module_dir=/usr/lib/xorg/modules/drivers/$(MACH64)

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += system/header/header-drm

# Auto-generated dependencies
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/server/xorg
