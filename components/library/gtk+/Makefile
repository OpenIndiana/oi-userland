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
# Copyright 2016 Alexander Pyhalov
#

BUILD_BITS= 64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gtk+
COMPONENT_VERSION= 2.24.33
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= GTK+ - GIMP Toolkit Library for creation of graphical user interfaces
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:ac2ac757f5942d318a311a54b0c80b5ef295f299c2a73c632f6bfb1ff49cc6da
COMPONENT_ARCHIVE_URL= https://download.gnome.org/sources/$(COMPONENT_NAME)/2.24/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://www.gtk.org/

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

gcc_OPT = -O2
CFLAGS += -I/usr/X11/include

COMPONENT_PREP_ACTION = \
          ( cd $(@D) && PATH="$(PATH)" libtoolize --force && \
          aclocal -I ./m4 &&\
          gtkdocize &&\
          autoheader &&\
          automake -a -f -c --gnu &&\
          autoconf )

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --enable-shm
CONFIGURE_OPTIONS += --with-gdktarget=x11
CONFIGURE_OPTIONS += --enable-explicit-deps=yes
CONFIGURE_OPTIONS += --enable-man

CONFIGURE_ENV    += XGETTEXT=/usr/gnu/bin/xgettext
CONFIGURE_ENV    += MSGFMT=/usr/gnu/bin/msgfmt
CONFIGURE_ENV    += PYTHON=$(PYTHON)
CONFIGURE_ENV    += GLIB_GENMARSHAL=/usr/bin/glib-genmarshal
CONFIGURE_ENV    += GLIB_MKENUMS=/usr/bin/glib-mkenums

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

COMPONENT_POST_INSTALL_ACTION = ( $(GSED) -i -e 's:/usr/bin/env python:$(PYTHON):' $(PROTO_DIR)/usr/bin/gtk-builder-convert )

COMPONENT_TEST_TRANSFORMS += \
	' -e "/check in/p" ' \
	' -e "/======/p" ' \
	' -e "/summary/p" '

# Manually added dependencies
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
