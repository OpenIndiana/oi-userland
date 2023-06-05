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

COMPONENT_NAME=         xscope
COMPONENT_VERSION=      1.4.4
COMPONENT_FMRI=         x11/diagnostic/xscope
COMPONENT_SUMMARY=      xscope - X Window Protocol Viewer
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:820d6708fce16e449a3cb8e62c2a0f49551e589d6595633deab82643e6a90c83
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CPPFLAGS+= -DFD_SETSIZE=256

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
