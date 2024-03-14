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
# Copyright 2019 Aurelien Larcher
#

BUILD_BITS= 32_and_64
BUILD_STYLE= meson
COMPONENT_X11_DEFAULTS= no
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= glu
COMPONENT_VERSION= 9.0.3
COMPONENT_SUMMARY= libglu part of the Mesa 3-D Graphics Library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:bd43fe12f374b1192eb15fe20e45ff456b9bc26ab57f0eee919f96ca0f8a330f
COMPONENT_ARCHIVE_URL=	ftp://ftp.freedesktop.org/pub/mesa/glu/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.mesa3d.org/
COMPONENT_FMRI=	x11/library/glu
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL=0

CONFIGURE_OPTIONS += -Dgl_provider=gl

LDFLAGS= -L$(X11_SERVERLIBS_DIR) -R$(X11_SERVERLIBS_DIR) 

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
