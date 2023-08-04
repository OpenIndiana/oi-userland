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
# Copyright 2016-2017 Predrag Zečević.  All rights reserved.
# Copyright 2020 Andreas Wacknitz
#

BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         geany
COMPONENT_VERSION=      1.38
COMPONENT_REVISION=     4
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_FMRI=         editor/geany
COMPONENT_SUMMARY=      A fast and lightweight IDE
COMPONENT_DESCRIPTION= Small and fast IDE, which has only a few dependencies from other package (independent on DE)
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:abff176e4d48bea35ee53037c49c82f90b6d4c23e69aed6e4a5ca8ccd3aad546
COMPONENT_ARCHIVE_URL=  https://download.geany.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.geany.org
COMPONENT_LICENSE=      GPLv2

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CFLAGS += -D_FILE_OFFSET_BITS=64

CONFIGURE_OPTIONS    += --enable-vte
CONFIGURE_OPTIONS    += --disable-html-docs
CONFIGURE_OPTIONS    += --disable-pdf-docs
CONFIGURE_OPTIONS    += --enable-api-docs
CONFIGURE_OPTIONS    += --enable-gtkdoc-header
CONFIGURE_OPTIONS    += --enable-the-force

# Manually added build dependencies:
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/c++/graphite2
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxau
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxdmcp
REQUIRED_PACKAGES += x11/library/libxevie
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxscrnsaver
REQUIRED_PACKAGES += x11/library/mesa
REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
