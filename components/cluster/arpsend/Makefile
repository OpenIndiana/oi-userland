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

BUILD_STYLE= configure
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         arpsend
COMPONENT_VERSION=      1.2.5
COMPONENT_SUMMARY=      arpsend sends an Ethernet frame containing an IP ARP request or reply packet containing fields you specify.
COMPONENT_PROJECT_URL=  https://www.net.princeton.edu/software/$(COMPONENT_NAME)
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:a96fd5293c1b0f53238194faffa9f16c05aacd02be8d77fadfb18a1190f06ad6
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE) 
COMPONENT_FMRI=         utility/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_LICENSE=      BSD, GPLv2, LGPLv2

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_OPTIONS += --with-libnet=$(USRDIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libnet
