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
# Copyright 2016 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved. 
#

BUILD_STYLE=configure
BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         arpsend
COMPONENT_VERSION=      1.2.4
COMPONENT_REVISION=     0
COMPONENT_FMRI=         utility/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_PROJECT_URL=  https://www.net.princeton.edu/software/$(COMPONENT_NAME)/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:d96c1a54f8ee21457ac0f4098d110c96d3dff7b9f5e13e84a36fdb6632014aab
COMPONENT_ARCHIVE_URL=  https://www.net.princeton.edu/software/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE) 
COMPONENT_LICENSE=      LGPLv2
COMPONENT_SUMMARY=      arpsend sends an Ethernet frame containing an IP ARP request or reply packet containing fields you specify.

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --with-libnet=$(USRDIR)
GPATCH_FLAGS += -l

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D)) 

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libnet
