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

X11_CATEGORY=LIB
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=    libXinerama
COMPONENT_VERSION= 1.1.4
COMPONENT_FMRI=    x11/library/libxinerama
COMPONENT_SUMMARY= libXinerama - X PanoramiX extension library 
COMPONENT_ARCHIVE_HASH= \
  sha256:0008dbd7ecf717e1e507eed1856ab0d9cf946d03201b85d5dcf61489bb02d720

include $(WS_MAKE_RULES)/common.mk

CPPFLAGS+=	-D SUNSOFT

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared

LD_OPTIONS += -M$(COMPONENT_DIR)/mapfile-vers

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
