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

COMPONENT_NAME=     xcalc
COMPONENT_VERSION=  1.0.7
COMPONENT_FMRI=     x11/xcalc
COMPONENT_SUMMARY=  xcalc - scientific calculator for X
COMPONENT_CLASSIFICATION= Applications/Accessories
COMPONENT_PROJECT_URL= $(XORG_PROJECT_URL)
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:70d271d1655f90ed0d4011f58022c441e1832f01eb3450c691799b131b557f21
COMPONENT_ARCHIVE_URL= $(XORG_APP_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=  MIT License

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
