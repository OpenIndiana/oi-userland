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

COMPONENT_NAME=     setxkbmap
COMPONENT_VERSION=  1.3.2
COMPONENT_FMRI=     x11/keyboard/setxkbmap
COMPONENT_SUMMARY=  the setxkbmap keyboard configuration utility
COMPONENT_ARCHIVE_HASH= \
  sha256:8ff27486442725e50b02d7049152f51d125ecad71b7ce503cfa09d5d8ceeb9f5

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxkbfile
