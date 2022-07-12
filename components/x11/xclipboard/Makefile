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

COMPONENT_NAME=           xclipboard
COMPONENT_VERSION=        1.1.4
COMPONENT_FMRI=           x11/xclipboard
COMPONENT_CLASSIFICATION= Applications/Accessories
COMPONENT_SUMMARY=  xclipboard − X clipboard client
COMPONENT_ARCHIVE_EXTENSION= .tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:c40cb97f6c8597ba74a3de5c188d4429f686e4d395b85dac0ec8c7311bdf3d10

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxkbfile
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
