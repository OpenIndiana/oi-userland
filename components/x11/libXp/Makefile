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

COMPONENT_NAME=    libXp
COMPONENT_VERSION= 1.0.4
COMPONENT_FMRI=    x11/library/libxp
COMPONENT_SUMMARY= libXp - X print library
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:1f19e3b8e82a34a8fd9889a7d9af0abe8588cb03fb57c37c569634cf3b9df1a4

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV+= XPRINT_LIBS='-lX11 -lXext'

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i )

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
