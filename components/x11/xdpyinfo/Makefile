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

COMPONENT_NAME=     xdpyinfo
COMPONENT_VERSION=  1.3.2
COMPONENT_REVISION= 1
COMPONENT_FMRI=     x11/diagnostic/xdpyinfo
COMPONENT_SUMMARY=  xdpyinfo − display information utility for X
COMPONENT_ARCHIVE_HASH= \
  sha256:30238ed915619e06ceb41721e5f747d67320555cc38d459e954839c189ccaf51

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libdmx
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxtst
REQUIRED_PACKAGES += x11/library/libxxf86misc
REQUIRED_PACKAGES += x11/library/libxxf86vm
