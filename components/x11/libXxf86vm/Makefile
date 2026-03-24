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

COMPONENT_NAME=			libXxf86vm
COMPONENT_VERSION=		1.1.7
COMPONENT_SUMMARY= 		libXxf86vm - VidMode extension for modifying video attributes
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:ae50c0f669e0af5a67cc4cd0f54f21d64a64d2660af883e80e95d3fe51b945d8
COMPONENT_FMRI=			x11/library/libxxf86vm
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += LIB_MAN_SUFFIX=3xxf86vm

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
