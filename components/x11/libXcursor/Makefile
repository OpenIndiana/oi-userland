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

COMPONENT_NAME=    libXcursor
COMPONENT_VERSION= 1.2.0
COMPONENT_FMRI=    x11/library/libxcursor
COMPONENT_SUMMARY= libXcursor - Client-side cursor loading library
COMPONENT_ARCHIVE_HASH= \
  sha256:3ad3e9f8251094af6fe8cb4afcf63e28df504d46bfa5a5529db74a505d628782

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --with-icondir=/usr/share/icons
CONFIGURE_OPTIONS+= --with-cursorpath='~/.icons:/usr/share/icons:/usr/share/pixmaps'


# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxrender
