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
# Copyright 2016 Aurelien Larcher
#

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=     viewres
COMPONENT_VERSION=  1.0.5
COMPONENT_REVISION= 1
COMPONENT_FMRI=     x11/viewres
COMPONENT_SUMMARY=  viewres - Xt widget class browser
COMPONENT_ARCHIVE_HASH= \
  sha256:5ed818e84c39bcf26dadc885c9860432b85843caad3621e26d99edea660ae3d7

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
