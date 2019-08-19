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

COMPONENT_NAME=     xgamma
COMPONENT_VERSION=  1.0.6
COMPONENT_REVISION= 1
COMPONENT_FMRI=     x11/xgamma
COMPONENT_SUMMARY=  xgamma - monitor gamma correction setting utility
COMPONENT_ARCHIVE_HASH= \
  sha256:0ef1c35b5c18b1b22317f455c8df13c0a471a8efad63c89c98ae3ce8c2b222d3

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxxf86vm
