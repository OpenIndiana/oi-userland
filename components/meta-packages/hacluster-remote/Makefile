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
# Copyright 2017 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           hacluster-remote
COMPONENT_VERSION=	      1.0
COMPONENT_FMRI=           metapackages/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Meta Packages/Group Packages
COMPONENT_SUMMARY=	      High availaiblity cluster with pacemaker-remote and pcsd managgement gui

include $(WS_MAKE_RULES)/ips.mk

download:

build:

install:
	[ -d $(PROTO_DIR) ] || mkdir -p $(PROTO_DIR)

clean:
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)
