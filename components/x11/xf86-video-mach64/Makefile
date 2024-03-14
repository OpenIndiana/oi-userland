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

COMPONENT_NAME= xf86-video-mach64
COMPONENT_VERSION= 6.9.7
COMPONENT_SUMMARY= xf86-video-mach64 - MACH64 driver for the Xorg X server
COMPONENT_FMRI= x11/server/xorg/driver/xorg-video-mach64
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:50d78abffa7c8227e6f187976f23a244ae2095e97f08de275529b70fba9481ba

include $(WS_MAKE_RULES)/common.mk

CFLAGS+= -D__EXTENSIONS__
# Paths to find libraries/modules to link with 

LD_OPTIONS+= \
        -L$(X11_SERVERMODS_DIR) -R$(X11_SERVERMODS_DIR) \
        -lexa -lint10 -lpciaccess -lfb -lpixman-1 -lshadowfb -lvbe

# - Disable DRI since the kernel module isn't ported
CONFIGURE_OPTIONS += --disable-dri

CONFIGURE_OPTIONS += --enable-exa
CONFIGURE_OPTIONS += --enable-xaa

CONFIGURE_ENV += with_xorg_module_dir=/usr/lib/xorg/modules/drivers/$(MACH64)

COMPONENT_BUILD_ARGS += $(COMPONENT_COMMON_ARGS)
COMPONENT_INSTALL_ARGS += $(COMPONENT_COMMON_ARGS)

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += system/header/header-drm

# Auto-generated dependencies
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/server/xorg
