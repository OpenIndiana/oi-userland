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
BUILD_BITS=64_and_32

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= libXdmcp
COMPONENT_VERSION= 1.1.3
COMPONENT_SUMMARY= libXdmcp - X Display Manager Control Protocol (XDMCP) library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL= $(XORG_PROJECT_URL)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:20523b44aaa513e17c009e873ad7bbc301507a3224c232610ce2e099011c6529
COMPONENT_ARCHIVE_URL= $(XORG_LIB_BASE_URL)/$(COMPONENT_ARCHIVE)
LD_OPTIONS += -M $(COMPONENT_DIR)/mapfile-vers

include $(WS_MAKE_RULES)/common.mk

# Build dependencies
REQUIRED_PACKAGES += x11/header/xproto

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
