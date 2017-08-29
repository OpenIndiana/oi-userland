#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017, Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nvidia
COMPONENT_FMRI=		driver/graphics/nvidia
COMPONENT_VERSION=	1.0.0
COMPONENT_SUMMARY=	NVIDIA Graphics System Software
COMPONENT_DESCRIPTION=	X and OpenGL Drivers for NVIDIA graphics (dispatcher package for available versions for different hardware)
COMPONENT_PROJECT_URL=	http://www.nvidia.com/object/solaris-display-archive.html

include $(WS_MAKE_RULES)/ips.mk

download:

prep:

build:

install:
	[ -d $(PROTO_DIR) ] || mkdir -p $(PROTO_DIR)

clean:
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)
