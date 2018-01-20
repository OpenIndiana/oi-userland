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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= geany
COMPONENT_VERSION= 1.31
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_FMRI=editor/geany
COMPONENT_SUMMARY= A fast and lightweight IDE
COMPONENT_DESCRIPTION= Small and fast IDE, which has only a few dependencies from other package (independent on DE)
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:30fdb906bb76c4251a8bcf83ee267db28c26ef6ab867668a782cec1164a3aba5
COMPONENT_ARCHIVE_URL= http://download.geany.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.geany.org/Main/HomePage
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS    += --enable-vte
CONFIGURE_OPTIONS    += --disable-html-docs
CONFIGURE_OPTIONS    += --disable-pdf-docs
CONFIGURE_OPTIONS    += --enable-api-docs
CONFIGURE_OPTIONS    += --enable-gtkdoc-header
CONFIGURE_OPTIONS    += --enable-the-force

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/c++/graphite2
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
REQUIRED_PACKAGES += system/library/math
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
