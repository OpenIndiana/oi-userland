#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= bnx

COMPONENT_VERSION= 7.8.2
IPS_COMPONENT_VERSION= 0.5.11
HUMAN_VERSION=$(COMPONENT_VERSION)
COMPONENT_SUMMARY= Broadcom NetXtreme II Gigabit Ethernet Adapter Driver
COMPONENT_SRC= BRCMbnx
COMPONENT_ARCHIVE= $(COMPONENT_SRC)-S11-i386-$(COMPONENT_VERSION).tar.Z
COMPONENT_ARCHIVE_HASH= \
  sha256:0ef103dd18c96668f968b55f63c6b6c38d1711fd921dffc0d23047a39d708d40
# Note, we are not sure if we can distribute this source file, so it is available
# only from our build servers
# However, you can manually download Solaris GLDv3 driver from 
# http://www.broadcom.com/support/ethernet_nic/netxtremeii.php ,
# extract BRCMbnx-S11-i386-7.8.2.tar.Z and put it in component dir.
COMPONENT_ARCHIVE_URL= \
  http://dlc-int.openindiana.org/hipster/broadcom/BRCMbnx-S11-i386-7.8.2.tar.Z
COMPONENT_PROJECT_URL = http://www.broadcom.com/support/ethernet_nic/netxtremeii.php

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk

CLEAN_PATHS += $(BUILD_DIR)

$(BUILD_32):	$(SOURCE_DIR)/.prep
	$(MKDIR) $(@D)
	$(TOUCH) $@

$(INSTALL_32): $(BUILD_32)
	$(MKDIR) $(PROTO_DIR) 
	cp -a $(SOURCE_DIR)/reloc/* $(PROTO_DIR)
	$(TOUCH) $@

build: $(BUILD_32)

install: $(INSTALL_32)
