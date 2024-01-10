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
BUILD_BITS= 64
X11_CATEGORY= UTIL
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           imake
COMPONENT_VERSION=        1.0.10
COMPONENT_SUMMARY=  imake - makefile generation tool
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH=   sha256:75decbcea8d7b354cf36adc9675e53c4790ee3de56a14bd87b42c8e8aad2ecf5
COMPONENT_FMRI=           developer/build/imake
COMPONENT_LICENSE_FILE=   COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --enable-mkdirhier
CONFIGURE_OPTIONS += --disable-ccmakedep
CONFIGURE_OPTIONS += --disable-cleanlinks
CONFIGURE_OPTIONS += --disable-makeg
CONFIGURE_OPTIONS += --disable-mergelib
CONFIGURE_OPTIONS += --disable-mkhtmlindex
CONFIGURE_OPTIONS += --disable-revpath
CONFIGURE_OPTIONS += RAWCPP=/usr/lib/cpp

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
