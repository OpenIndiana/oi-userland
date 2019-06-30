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

COMPONENT_NAME=           xcompmgr
COMPONENT_VERSION=        1.1.8
COMPONENT_FMRI=           desktop/window-manager/xcompmgr
COMPONENT_SUMMARY=  xcompmgr - X compositing manager
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_PROJECT_URL= $(XORG_PROJECT_URL)
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:0b89daf4f060fa3fa83cca862c45d531fef7121b5d06552c1d73d396ad9a7243
COMPONENT_ARCHIVE_URL= $(XORG_APP_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MIT License

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxrender
