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
BUILD_BITS=64_and_32

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           libXrandr
COMPONENT_VERSION=        1.5.2
COMPONENT_FMRI=           x11/library/libxrandr
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  libXrandr - X Resize and Rotate extension library 
COMPONENT_PROJECT_URL=    $(XORG_PROJECT_URL)
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:8aea0ebe403d62330bb741ed595b53741acf45033d3bda1792f1d4cc3daee023
COMPONENT_ARCHIVE_URL=    $(XORG_LIB_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MIT License

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared

LD_OPTIONS += -M$(COMPONENT_DIR)/mapfile-vers

# Build dependencies
REQUIRED_PACKAGES += x11/header/xextproto
REQUIRED_PACKAGES += x11/header/randrproto
REQUIRED_PACKAGES += x11/header/renderproto

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrender
