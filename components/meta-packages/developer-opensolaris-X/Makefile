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
# Copyright 2021 Andreas Wacknitz. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		developer-opensolaris-X
COMPONENT_VERSION=	2
COMPONENT_SUMMARY=	Dependencies required to build the X Consolidation
COMPONENT_CLASSIFICATION=	Meta Packages/Group Packages
COMPONENT_FMRI=	developer/opensolaris/X

include ../../../make-rules/ips.mk

#PKGLINT=/bin/true

download:

prep:

build:

install:
	[ -d $(PROTO_DIR) ] || mkdir -p $(PROTO_DIR)

clean:
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)
