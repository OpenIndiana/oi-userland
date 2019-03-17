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
BUILD_BITS=64

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           bitmap
COMPONENT_VERSION=        1.0.9
COMPONENT_SUMMARY= bitmap - bitmap, bmtoa, and atobm utilities
COMPONENT_PROJECT_URL=    $(XORG_PROJECT_URL)
COMPONENT_FMRI=           image/editor/bitmap
COMPONENT_CLASSIFICATION= Applications/Graphics and Imaging
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:e0f3afad5272d796f54c33fa1b5bd1fb3f62843a54b28c87196d06a35123e5f5
COMPONENT_ARCHIVE_URL= $(XORG_APP_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MIT License

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Build dependencies
REQUIRED_PACKAGES += x11/data/xbitmaps

# Auto-generated
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
