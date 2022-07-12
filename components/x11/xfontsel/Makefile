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

COMPONENT_NAME=    xfontsel
COMPONENT_VERSION= 1.1.0
COMPONENT_SUMMARY= xfontsel - point and click selection of X11 font names
COMPONENT_FMRI=    x11/xfontsel
COMPONENT_ARCHIVE_EXTENSION= .tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:32938f671c706dc15644ceebf5daebbf0f2f1fe45afa2d06d2b905cc7d6c7de2

include $(WS_MAKE_RULES)/common.mk

CPPFLAGS+= -DXLOCALEDIR=\"$(USRSHARELOCALEDIR)\"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
