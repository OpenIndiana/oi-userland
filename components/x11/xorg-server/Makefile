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

COMPONENT_NAME= xorg-server
COMPONENT_VERSION= 1.7.7
COMPONENT_SUMMARY= Xorg - X11R7 X server
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:54c4d32bfeb8852adbea3ddae6981f3bc2eadb330124d9b35226c617c01926ff
COMPONENT_ARCHIVE_URL= \
  http://ftp.x.org/pub/individual/xserver/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.x.org/wiki/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_POST_UNPACK_ACTION +=  ( cp -r $(COMPONENT_DIR)/srcs/* $(SOURCE_DIR) )

PATCH_LEVEL=0

$(BUILD_32): $(SOURCE_DIR)/.prep

$(INSTALL_32): $(SOURCE_DIR)/.prep

build: $(BUILD_32)

install: $(INSTALL_32)
