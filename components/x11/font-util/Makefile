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

BUILD_BITS= 64
X11_CATEGORY= FONT
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= font-util
COMPONENT_VERSION= 1.4.0
COMPONENT_FMRI= x11/font-util
COMPONENT_SUMMARY= X.Org font package creation/installation utilities
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:9f724bf940128c7e39f7252bd961cd38cfac2359de2100a8bed696bf40d40f7d
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_INSTALL_ARGS += pkgconfigdir=/usr/share/pkgconfig

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
