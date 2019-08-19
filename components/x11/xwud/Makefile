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

COMPONENT_NAME=           xwud
COMPONENT_VERSION=        1.0.5
COMPONENT_SUMMARY=        xwud - viewer application for xwd images
COMPONENT_FMRI=           x11/xwud
COMPONENT_ARCHIVE_HASH= \
  sha256:99997051f8a892313f22edf41dab45864e86e7062ee9012d5dbb6a40fc6b10a9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
