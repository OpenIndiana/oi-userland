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
# Copyright 2015 Aurelien Larcher
#

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=     xkbprint
COMPONENT_VERSION=  1.0.4
COMPONENT_REVISION= 1
COMPONENT_FMRI=     x11/keyboard/xkbprint
COMPONENT_SUMMARY=  xkbprint - utility to print XKB keyboard layouts
COMPONENT_ARCHIVE_HASH= \
  sha256:0b3faab8fefad03dfb7e866f634cf859822801de6b5fc6cf5e0a62857ed93e12

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxkbfile
