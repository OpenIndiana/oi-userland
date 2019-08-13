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

COMPONENT_NAME=		X-incorporation
COMPONENT_VERSION=	0.5.11
COMPONENT_REVISION=	7
COMPONENT_SUMMARY=	X consolidation incorporation

include ../../../make-rules/ips.mk

#PKGLINT=/bin/true

download:

prep:

build:

install:
	[ -d $(PROTO_DIR) ] || mkdir -p $(PROTO_DIR)

clean:
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/motif/libdpstkxm
REQUIRED_PACKAGES += system/kernel/hardware-cursor
REQUIRED_PACKAGES += x11/library/dps
REQUIRED_PACKAGES += x11/library/libowconfig
REQUIRED_PACKAGES += x11/network/rstart
REQUIRED_PACKAGES += x11/network/x11-network-proxies
