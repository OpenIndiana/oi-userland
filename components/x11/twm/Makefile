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

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= twm
COMPONENT_VERSION= 1.0.10
COMPONENT_SUMMARY=  twm - Tab Window Manager for the X Window System
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:6449eadca16ce0f0d900605b0cc020b95f40619261b7beccfb46bcc1836445d7
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/app/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.freedesktop.org/wiki/
COMPONENT_FMRI= desktop/window-manager/twm
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION= System/X11

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS+= --sysconfdir=/etc

build: $(BUILD_64)

install: $(INSTALL_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxt
