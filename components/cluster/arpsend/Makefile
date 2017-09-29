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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=   arpsend
COMPONENT_VERSION=  1.2.3
COMPONENT_REVISION= 1
COMPONENT_FMRI= utility/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_PROJECT_URL=  https://www.net.princeton.edu/software/$(COMPONENT_NAME)/
COMPONENT_SRC=    $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:5f7664bfe556225a94c3d6736eec21d88fd6a81af3b7fed0403de49488406757
COMPONENT_ARCHIVE_URL= https://www.net.princeton.edu/software/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE) 
COMPONENT_LICENSE= LGPLv2
COMPONENT_SUMMARY= arpsend sends an Ethernet frame containing an IP ARP request or reply packet containing fields you specify.

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk


CONFIGURE_OPTIONS += --with-libnet=/usr

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D)) 

CONFIGURE_BINDIR.64= $(CONFIGURE_BINDIR.32)

build:          $(BUILD_64)

install:        $(INSTALL_64)

test:           $(TESTS_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libnet
