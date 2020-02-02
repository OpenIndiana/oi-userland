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
# Copyright 2017 Aurelien Larcher
#

X11_CATEGORY=DRIVER
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= xf86-video-vboxvideo
COMPONENT_VERSION= 1.0.0
# Use version string from Xorg module
IPS_COMPONENT_VERSION= 1.0.1
COMPONENT_REVISION= 4
COMPONENT_FMRI= x11/server/xorg/driver/xorg-video-vboxvideo
COMPONENT_SUMMARY= xf86-video-vboxvideo - VirtualBox UMS driver for the Xorg X server
COMPONENT_ARCHIVE_HASH= \
  sha256:7fb6a3bfbcbe95438617f55a2f7ace4c0edec8ea8b7007777f389438b40cbfa4

include $(WS_MAKE_RULES)/common.mk

CFLAGS+= -std=gnu99

LD_OPTIONS+= \
	     -L$(X11_SERVERMODS_DIR) -R$(X11_SERVERMODS_DIR) \
	     -L$(MESA_XSERVERMODS_EXTENSIONS_DIR) -R$(MESA_XSERVERMODS_EXTENSIONS_DIR) \
	     -L$(X11_SERVERMODS_EXTENSIONS_DIR) -R$(X11_SERVERMODS_EXTENSIONS_DIR) \
	     -L$(X11_SERVERLIBS_DIR) -R$(X11_SERVERLIBS_DIR)

CONFIGURE_OPTIONS+= --with-xorg-module-dir=$(X11_SERVERMODS_DIR)$(SERVERMOD_SUBDIR)

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += system/header/header-drm

# Auto-generated dependencies
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libdrm
REQUIRED_PACKAGES += x11/server/xorg
