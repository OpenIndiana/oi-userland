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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ftgl
COMPONENT_VERSION=	2.1.3.5
HUMAN_VERSION=		2.1.3~rc5
COMPONENT_REVISION=	1
COMPONENT_FMRI=		library/x11/ftgl
COMPONENT_PROJECT_URL=	https://sourceforge.net/projects/ftgl
COMPONENT_SUMMARY=	OpenGL FreeType fonts rendering library
COMPONENT_DESCRIPTION=	FTGL is a free cross-platform Open Source C++ library that uses Freetype2 to simplify rendering fonts in OpenGL applications. FTGL supports bitmaps, pixmaps, texture maps, outlines, polygon mesh, and extruded polygon rendering modes.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-2.1.3-rc5.tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:5458d62122454869572d39f8aa85745fc05d5518001bcefa63bd6cbb8d26565b
COMPONENT_ARCHIVE_URL= \
  $(COMPONENT_PROJECT_URL)/files/FTGL%20Source/$(HUMAN_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MIT
COMPONENT_CLASSIFICATION= System/X11

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --with-x
CONFIGURE_ENV += LIBS="-lm"

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += x11/library/freeglut

# Build dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/glu
