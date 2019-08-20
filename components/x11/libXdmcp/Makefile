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

X11_CATEGORY=LIB
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=    libXdmcp
COMPONENT_VERSION= 1.1.3
COMPONENT_FMRI=    x11/library/libxdmcp
COMPONENT_SUMMARY= libXdmcp - X Display Manager Control Protocol (XDMCP) library
COMPONENT_ARCHIVE_HASH= \
  sha256:20523b44aaa513e17c009e873ad7bbc301507a3224c232610ce2e099011c6529
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

LD_OPTIONS += -M $(COMPONENT_DIR)/mapfile-vers

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
