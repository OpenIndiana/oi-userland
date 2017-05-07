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

COMPONENT_NAME=		sun-ext-protos
COMPONENT_VERSION=	0.1
COMPONENT_SUMMARY=	headers & documentation for X11 protocol extensions created by Sun
COMPONENT_PROJECT_URL = https://hg.java.net/hg/solaris-x11~x-s12-clone
COMPONENT_FMRI= x11/header/sun-ext-protos
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= sun-ext-protos.license
COMPONENT_CLASSIFICATION= Development/X11


include ../../../make-rules/ips.mk

download:

prep:

build:

install:
	$(RM) -rf $(PROTO_DIR)
	$(MKDIR) $(PROTO_DIR)/usr/share/doc/sun-ext-protos
	$(MKDIR) $(PROTO_DIR)/usr/include/X11/extensions
	cp $(COMPONENT_DIR)/files/include/*  $(PROTO_DIR)/usr/include/X11/extensions
	cp $(COMPONENT_DIR)/files/docs/*  $(PROTO_DIR)/usr/share/doc/sun-ext-protos

clean:
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)
