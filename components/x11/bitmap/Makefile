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
COMPONENT_VERSION= 1.1.1
COMPONENT_SUMMARY= bitmap - bitmap, bmtoa, and atobm utilities
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:63d42eb63fe48198b39344af49949e5e424cc62ce8d722781fdad4a4fa3426e6
COMPONENT_FMRI=    image/editor/bitmap
COMPONENT_CLASSIFICATION= Applications/Graphics and Imaging
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

# Manually added build dependencies
REQUIRED_PACKAGES += x11/data/xbitmaps

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
