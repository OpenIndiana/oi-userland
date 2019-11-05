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
BUILD_BITS=64

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           imake
COMPONENT_VERSION=        1.0.8
COMPONENT_FMRI=           developer/build/imake
COMPONENT_CLASSIFICATION= Development/X11
COMPONENT_SUMMARY=  imake - makefile generation tool
COMPONENT_PROJECT_URL=    $(XORG_PROJECT_URL)
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:b8d2e416b3f29cd6482bcffaaf19286d32917a164d07102a0e531ccd41a2a702
COMPONENT_ARCHIVE_URL=    $(XORG_UTIL_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=        MIT License

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS+= --enable-mkdirhier
CONFIGURE_OPTIONS+= --disable-ccmakedep
CONFIGURE_OPTIONS+= --disable-cleanlinks
CONFIGURE_OPTIONS+= --disable-makeg
CONFIGURE_OPTIONS+= --disable-mergelib
CONFIGURE_OPTIONS+= --disable-mkhtmlindex
CONFIGURE_OPTIONS+= --disable-revpath
CONFIGURE_OPTIONS+= RAWCPP=/usr/lib/cpp

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
