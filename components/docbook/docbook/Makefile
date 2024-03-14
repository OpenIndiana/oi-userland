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
# Copyright 2023 Friedrich Kink. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= docbook
COMPONENT_VERSION= 2.30.0
COMPONENT_REVISION= 6
COMPONENT_SUMMARY= docbook SGML and XML stylesheets
COMPONENT_FMRI= data/docbook
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Documentation

include $(WS_MAKE_RULES)/ips.mk

install:
	[ -d $(PROTO_DIR) ] || mkdir -p $(PROTO_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
