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
# Copyright 2015 Alexander Pyhalov
#

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= iceauth
COMPONENT_VERSION= 1.0.8
COMPONENT_REVISION= 1
COMPONENT_FMRI= x11/iceauth
COMPONENT_SUMMARY= ICE authority file utility
COMPONENT_ARCHIVE_HASH= \
  sha256:e6ee213a217265cc76050e4293ea70b98c32dce6505c6421227efbda62ab60c6
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libice
