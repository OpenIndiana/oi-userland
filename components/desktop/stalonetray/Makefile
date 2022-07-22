#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2016 Sergey Avseyev
#
BUILD_STYLE=configure
BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         stalonetray
COMPONENT_VERSION=      0.8.3
COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  http://stalonetray.sourceforge.net/
COMPONENT_SUMMARY=      stalonetray is a stand-alone freedesktop.org and KDE system tray (notification area) for X Window System/X11 (e.g. X.Org or XFree86). It has full XEMBED support and minimal dependencies: an X11 lib only. Stalonetray works with virtually any EWMH-compliant window manager.
COMPONENT_FMRI=         desktop/stalonetray
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:36548a588b2d466913423245dda6ffb6313132cd0cec635a117d37b3dab5fd4c
COMPONENT_ARCHIVE_URL=  http://downloads.sourceforge.net/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxpm
