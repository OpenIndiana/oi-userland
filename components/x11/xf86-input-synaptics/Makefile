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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= xf86-input-synaptics
COMPONENT_VERSION= 1.9.1
COMPONENT_SUMMARY= xf86-input-synaptics - Synaptics touchpad driver for X.Org
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org
COMPONENT_FMRI = x11/server/xorg/driver/xorg-input-synaptics
COMPONENT_CLASSIFICATION= Drivers/Other Peripherals
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/driver/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:7af83526eff1c76e8b9e1553b34245c203d029028d8044dd9dcf71eef1001576
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_BINDIR.32=/usr/lib/xorg
CONFIGURE_BINDIR.64=/usr/lib/xorg/$(MACH64)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxtst
REQUIRED_PACKAGES += x11/library/libpthread-stubs
REQUIRED_PACKAGES += x11/header/inputproto
