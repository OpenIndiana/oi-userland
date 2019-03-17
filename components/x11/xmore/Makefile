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
# Copyright 2019 Aurelien Larcher
#
BUILD_BITS=64

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=     xmore
COMPONENT_VERSION=  1.0.3
COMPONENT_FMRI=     x11/xmore
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  xmore - a plain text display program for the X Window System
COMPONENT_PROJECT_URL= $(XORG_PROJECT_URL)
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:644a1e0d5182d7708d413722d0579a587dc56b9a8cb60640df076d302e09251b
COMPONENT_ARCHIVE_URL= $(XORG_APP_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=  MIT License

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
