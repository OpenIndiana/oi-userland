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
# Copyright 2018 Harry Liebel <hliebel@gmail.com>
# Copyright 2021 Andreas Wacknitz
#

BUILD_BITS=	64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ftgl
COMPONENT_VERSION=	2.4.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	OpenGL FreeType fonts rendering library
COMPONENT_DESCRIPTION=	FTGL is a free cross-platform Open Source C++ library that uses Freetype2 to simplify rendering fonts in OpenGL applications. FTGL supports bitmaps, pixmaps, texture maps, outlines, polygon mesh, and extruded polygon rendering modes.
COMPONENT_PROJECT_URL=	https://github.com/frankheckenbach/ftgl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:aa97da1c3442a8fd3941037655df18016d70b5266381c81d81e8b5335f196ea8
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		library/x11/ftgl
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION += ( cd $(@D) ; $(CONFIG_SHELL) autogen.sh );

CONFIGURE_ENV += LIBS="-lm"

CONFIGURE_OPTIONS += --with-x
CONFIGURE_OPTIONS += --enable-static=

# Manually added build dependencies
REQUIRED_PACKAGES += x11/library/freeglut

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/glu
