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

X11_CATEGORY=DRIVER
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= xf86-input-synaptics
COMPONENT_VERSION= 1.9.1
COMPONENT_REVISION= 2
COMPONENT_FMRI= x11/server/xorg/driver/xorg-input-synaptics
COMPONENT_SUMMARY= xf86-input-synaptics - Synaptics touchpad driver for X.Org
COMPONENT_ARCHIVE_HASH= \
  sha256:7af83526eff1c76e8b9e1553b34245c203d029028d8044dd9dcf71eef1001576

include $(WS_MAKE_RULES)/common.mk

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += x11/library/libpthread-stubs

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxtst
