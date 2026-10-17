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

COMPONENT_NAME= xf86-video-trident
COMPONENT_VERSION= 1.4.0
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_FMRI= x11/server/xorg/driver/xorg-video-trident
COMPONENT_SUMMARY= xf86-video-trident - Trident video driver for the Xorg X server
COMPONENT_ARCHIVE_HASH= \
	sha256:7f76219ca7d7dc6061aa3c2aa59bc2a63895b8e6217e413ce315949f57b0189b

include $(WS_MAKE_RULES)/common.mk

LD_OPTIONS= \
        -L$(X11_SERVERMODS_DIR) -R$(X11_SERVERMODS_DIR) \
        -L$(X11_SERVERLIBS_DIR) -R$(X11_SERVERLIBS_DIR) \
        -lexa -lint10 -lpciaccess -lpixman-1 -lshadow -lvgahw \
        -lm

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols

# Auto-generated dependencies
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/server/xorg
