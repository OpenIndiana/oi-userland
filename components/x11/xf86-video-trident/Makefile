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
COMPONENT_VERSION= 1.3.8
COMPONENT_REVISION= 3
COMPONENT_FMRI= x11/server/xorg/driver/xorg-video-trident
COMPONENT_SUMMARY= xf86-video-trident - Trident video driver for the Xorg X server
COMPONENT_ARCHIVE_HASH= \
  sha256:9e5119d974c3e2221994542d35e3a0b3426a441869ddd6dd08a84f324856ac3f

include $(WS_MAKE_RULES)/common.mk

LD_OPTIONS= \
        -L$(X11_SERVERMODS_DIR) -R$(X11_SERVERMODS_DIR) \
        -L$(X11_SERVERLIBS_DIR) -R$(X11_SERVERLIBS_DIR) \
        -lexa -lfb -lint10 -lpciaccess -lpixman-1 -lshadow -lvbe -lvgahw \
        -lm

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols

# Auto-generated dependencies
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/server/xorg
