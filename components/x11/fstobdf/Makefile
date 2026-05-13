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

COMPONENT_NAME=     fstobdf
COMPONENT_VERSION=  1.0.8
COMPONENT_SUMMARY=  the fstobdf utility to retrieve bdf fonts from an xfs font server
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:69be41c4d5093bbc3f04c9af6fa9497ad8e931e8d3f687412a66885fe81aa46d
COMPONENT_FMRI=     x11/xfs/fstobdf

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libfs
REQUIRED_PACKAGES += x11/library/libx11
# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libfs
REQUIRED_PACKAGES += x11/library/libx11
