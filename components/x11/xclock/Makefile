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
# Copyright 2015 Alexander Pyhalov
#
BUILD_BITS=64

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= xclock
COMPONENT_VERSION= 1.0.8
COMPONENT_FMRI= x11/xclock
COMPONENT_SUMMARY= xclock - analog / digital clock for X
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_PROJECT_URL= $(XORG_PROJECT_URL)
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:930820483a36f1f1ce1bf52b648865629a16082641e12c5cf2b5045815fc2255
COMPONENT_ARCHIVE_URL= $(XORG_APP_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Build dependencies
REQUIRED_PACKAGES += x11/header/xproto

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxkbfile
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
