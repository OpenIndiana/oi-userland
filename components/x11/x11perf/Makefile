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

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=    x11perf
COMPONENT_VERSION= 1.6.2
COMPONENT_SUMMARY= x11perf - X11 server performance test program
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_URL= $(XORG_TEST_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:5a0e7cea47716ad07ceca38bbd07ae06459ee4d837b9c9dfc21ccb94e3e24fcc
COMPONENT_FMRI=    benchmark/x11perf
COMPONENT_CLASSIFICATION= System/X11

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --localstatedir=/var

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxmuu
REQUIRED_PACKAGES += x11/library/libxrender
