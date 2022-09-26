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

COMPONENT_NAME=		install-types
COMPONENT_VERSION=	0.1
COMPONENT_REVISION=	54
COMPONENT_SUMMARY=	A meta-packages that install common applications for ISOs

include $(WS_MAKE_RULES)/ips.mk

PKG_OPTIONS+= -I $(COMPONENT_DIR)/includes

download:

prep:

build:

install:
	[ -d $(PROTO_DIR) ] || mkdir -p $(PROTO_DIR)

clean:
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

# Auto-generated dependencies
