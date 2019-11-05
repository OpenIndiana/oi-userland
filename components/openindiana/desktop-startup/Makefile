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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		desktop-startup
COMPONENT_VERSION=	0.5.11
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://openindiana.org/
COMPONENT_SUMMARY=	Desktop startup scripts in xinitrc.d
COMPONENT_FMRI=		system/display-manager/desktop-startup
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Scripts
COMPONENT_LICENSE = CDDL
COMPONENT_LICENSE_FILE = opensolaris.license

include $(WS_TOP)/make-rules/ips.mk

download:

prep:

build:

install:
	[ -d $(PROTO_DIR) ] || mkdir -p $(PROTO_DIR)

clean:
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/bash
