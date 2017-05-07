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

COMPONENT_NAME=		gnu-common
COMPONENT_VERSION=	0.5.11

include $(WS_MAKE_RULES)/ips.mk

$(BUILD_32):	$(MAKEFILE_PREREQ)
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(TOUCH) $@

download:

prep:

build:	$(BUILD_32)

install:
	[ -d $(PROTO_DIR) ] || mkdir -p $(PROTO_DIR)

clean:
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)
