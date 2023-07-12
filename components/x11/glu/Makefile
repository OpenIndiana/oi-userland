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

BUILD_BITS=32_and_64
COMPONENT_X11_DEFAULTS=no

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= glu
COMPONENT_VERSION= 9.0.2
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= libglu part of the Mesa 3-D Graphics Library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:6e7280ff585c6a1d9dfcdf2fca489251634b3377bfc33c29e4002466a38d02d4
COMPONENT_ARCHIVE_URL=	ftp://ftp.freedesktop.org/pub/mesa/glu/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.mesa3d.org/

include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL=0

LDFLAGS= -L$(X11_SERVERLIBS_DIR) -R$(X11_SERVERLIBS_DIR) 

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
