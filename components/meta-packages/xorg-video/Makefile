#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2011 EveryCity Ltd. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xorg-video
COMPONENT_VERSION=	0.5.11
COMPONENT_REVISION= 3
COMPONENT_SUMMARY=	Xorg server video drivers group

include ../../../make-rules/ips.mk

download:

prep:

build:

install:
	[ -d $(PROTO_DIR) ] || mkdir -p $(PROTO_DIR)

clean:
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += consolidation/X/X-incorporation
REQUIRED_PACKAGES += x11/server/xorg/driver/xorg-video-ast
REQUIRED_PACKAGES += x11/server/xorg/driver/xorg-video-ati
REQUIRED_PACKAGES += x11/server/xorg/driver/xorg-video-cirrus
REQUIRED_PACKAGES += x11/server/xorg/driver/xorg-video-intel
REQUIRED_PACKAGES += x11/server/xorg/driver/xorg-video-mach64
REQUIRED_PACKAGES += x11/server/xorg/driver/xorg-video-mga
REQUIRED_PACKAGES += x11/server/xorg/driver/xorg-video-nv
REQUIRED_PACKAGES += x11/server/xorg/driver/xorg-video-openchrome
REQUIRED_PACKAGES += x11/server/xorg/driver/xorg-video-r128
REQUIRED_PACKAGES += x11/server/xorg/driver/xorg-video-savage
REQUIRED_PACKAGES += x11/server/xorg/driver/xorg-video-trident
REQUIRED_PACKAGES += x11/server/xorg/driver/xorg-video-vboxvideo
REQUIRED_PACKAGES += x11/server/xorg/driver/xorg-video-vesa
REQUIRED_PACKAGES += x11/server/xorg/driver/xorg-video-vmware
