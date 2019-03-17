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

COMPONENT_NAME=           xhost
COMPONENT_VERSION=        1.0.8
COMPONENT_FMRI=           x11/xhost
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  xhost - utility for mananging X server access control lists
COMPONENT_PROJECT_URL=    $(XORG_PROJECT_URL)
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:a2dc3c579e13674947395ef8ccc1b3763f89012a216c2cc6277096489aadc396
COMPONENT_ARCHIVE_URL=    $(XORG_APP_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MIT License

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Build dependencies
REQUIRED_PACKAGES += x11/header/xproto

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxau
REQUIRED_PACKAGES += x11/library/libxmuu
