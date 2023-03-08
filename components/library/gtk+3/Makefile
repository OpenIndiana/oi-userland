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
# Copyright 2017 Alexander Pyhalov
# Copyright 2019 Michal Nowak
# Copyright 2020 Marco van Wieringen
#

BUILD_BITS= 32_and_64
USE_COMMON_TEST_MASTER= no
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gtk+
COMPONENT_MJR_VERSION=	3.24
COMPONENT_VERSION=      $(COMPONENT_MJR_VERSION).34
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=      GTK+ - GIMP Toolkit Library for creation of graphical user interfaces
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:dbc69f90ddc821b8d1441f00374dc1da4323a2eafa9078e61edbe5eeefa852ec
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.gtk.org/
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_FMRI=         library/desktop/gtk3
COMPONENT_LICENSE=      LGPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CFLAGS += -I/usr/X11/include

# fixes possible textiter test failure
gcc_OPT = -O2
LD_Z_IGNORE=

# Uses isinf, etc. only available in c99 and newer
CFLAGS.gcc += -std=gnu11

COMPONENT_PREP_ACTION =	(cd $(@D) && \
				libtoolize --force && \
				aclocal -I ./m4 && \
				gtkdocize && \
				autoheader && \
				automake -a -f -c --gnu && \
				autoconf )

COMPONENT_PRE_CONFIGURE_ACTION =	( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS.32 = --sysconfdir=/etc
CONFIGURE_OPTIONS.64 = --sysconfdir=/etc/$(MACH64)
CONFIGURE_OPTIONS += --enable-explicit-deps=yes
CONFIGURE_OPTIONS += --enable-cloudprint
CONFIGURE_OPTIONS.64 += --enable-introspection
CONFIGURE_OPTIONS += --enable-man
CONFIGURE_OPTIONS += --disable-glibtest
CONFIGURE_OPTIONS += --disable-papi

CONFIGURE_ENV    += PERL=$(PERL)
CONFIGURE_ENV    += PYTHON=$(PYTHON)
CONFIGURE_ENV    += GLIB_COMPILE_SCHEMAS=/usr/bin/glib-compile-schemas
CONFIGURE_ENV    += GLIB_COMPILE_RESOURCES=/usr/bin/glib-compile-resources
CONFIGURE_ENV    += GLIB_GENMARSHAL=/usr/bin/glib-genmarshal
CONFIGURE_ENV    += GLIB_MKENUMS=/usr/bin/glib-mkenums

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

# for tests to pass
unexport SHELLOPTS
COMPONENT_TEST_TRANSFORMER = grep
COMPONENT_TEST_TRANSFORMS = '"^  /"'

# Test dependencies
REQUIRED_PACKAGES += gnome/theme/hicolor-icon-theme

# Build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += x11/server/xvfb

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/accessibility/at-spi2-atk
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libepoxy
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
