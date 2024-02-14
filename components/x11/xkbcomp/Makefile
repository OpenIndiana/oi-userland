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
# Copyright 2016-2020 Aurelien Larcher
#

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk
BUILD_BITS=32_and_64

COMPONENT_NAME=     xkbcomp
COMPONENT_VERSION=  1.4.7
COMPONENT_SUMMARY=  xkbcomp - compile XKB keyboard description
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:0a288114e5f44e31987042c79aecff1ffad53a8154b8ec971c24a69a80f81f77
COMPONENT_FMRI=     x11/keyboard/xkbcomp
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CPPFLAGS+= -DNO_ALLOCA 

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxkbfile
