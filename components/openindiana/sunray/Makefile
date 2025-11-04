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
# Copyright 2025	Carsten Grzemba
#

BUILD_STYLE = archive
BUILD_BITS = NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= oi-adaptions
COMPONENT_VERSION= 1.0
COMPONENT_SUMMARY=	script to patch SunRay Server for use on Openindiana
COMPONENT_FMRI=		sunray/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=      System/Virtualization
COMPONENT_LICENSE=	CDDL
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

install:
	mkdir -p $(PROTO_DIR)/opt/SUNWut/utils
	cp -rp $(COMPONENT_DIR)/files/* $(PROTO_DIR)/opt/SUNWut/utils
# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES.python += runtime/python
