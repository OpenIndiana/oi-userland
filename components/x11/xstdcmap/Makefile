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
BUILD_BITS=64

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           xstdcmap
COMPONENT_VERSION=        1.0.4
COMPONENT_FMRI=           x11/xstdcmap
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  xstdcmap - X11 standard colormap utility
COMPONENT_PROJECT_URL=    $(XORG_PROJECT_URL)
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:06898b3f1eaad0b205ff3c75bdefa3207868b889d4cb37b32b8267b2bbfe6f8b
COMPONENT_ARCHIVE_URL=    $(XORG_APP_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MIT License

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
