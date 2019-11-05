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

COMPONENT_NAME=           xkill
COMPONENT_VERSION=        1.0.5
COMPONENT_SUMMARY=        xkill - kill a client by its X resource
COMPONENT_FMRI=           x11/xkill
COMPONENT_ARCHIVE_HASH= \
  sha256:c5f0bb6a95e1ac7c4def8a657496d5d2f21ccd41eb47ef2c9ccb03fb6d6aff6b

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmuu
