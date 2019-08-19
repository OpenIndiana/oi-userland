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

COMPONENT_NAME=     transset
COMPONENT_VERSION=  1.0.2
COMPONENT_SUMMARY=  transset - Set transparency on a X window 
COMPONENT_FMRI=     x11/transset
COMPONENT_ARCHIVE_HASH= \
  sha256:4bac142ee7cfda574893b2f6b4e413dacd88a130c6dca5be1a9958e7c1451b21

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
