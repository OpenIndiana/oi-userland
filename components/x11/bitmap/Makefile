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
# Copyright 2015-2019 Aurelien Larcher
#

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=    bitmap
COMPONENT_VERSION= 1.1.0
COMPONENT_SUMMARY= bitmap - bitmap, bmtoa, and atobm utilities
COMPONENT_FMRI=    image/editor/bitmap
COMPONENT_CLASSIFICATION= Applications/Graphics and Imaging
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:8e86879c2feeece3f10e189330479cf51da0dd268355d1e3ee8a8497ab833690

include $(WS_MAKE_RULES)/common.mk

# Build dependencies
REQUIRED_PACKAGES += x11/data/xbitmaps

# Auto-generated
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
