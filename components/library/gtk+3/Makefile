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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gtk+
COMPONENT_VERSION= 3.14.15
COMPONENT_REVISION= 3
COMPONENT_SUMMARY= GTK+ - GIMP Toolkit Library for creation of graphical user interfaces
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:3ac87659112ced9e5ee5bd55d055faa881aafd040f26ca40b0d8ba0fa6509c83
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/3.14/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gtk.org/
COMPONENT_LICENSE= LGPLv2
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Libraries
COMPONENT_FMRI = library/desktop/gtk3

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CFLAGS += -I/usr/X11/include

COMPONENT_PREP_ACTION =	(cd $(@D) && libtoolize --force &&\
                                        aclocal -I ./m4 &&\
					gtkdocize &&\
                                        autoheader &&\
                                        automake -a -f -c --gnu &&\
                                        autoconf )

COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS.32 = --sysconfdir=/etc
CONFIGURE_OPTIONS.64 = --sysconfdir=/etc/$(MACH64)
CONFIGURE_OPTIONS += --with-native-locale=yes
CONFIGURE_OPTIONS += --with-xinput=xfree
CONFIGURE_OPTIONS += --enable-shm
CONFIGURE_OPTIONS += --enable-xim
CONFIGURE_OPTIONS += --enable-fbmanager
CONFIGURE_OPTIONS += --with-gdktarget=x11
CONFIGURE_OPTIONS += --enable-explicit-deps=yes
CONFIGURE_OPTIONS += --without-libjasper
CONFIGURE_OPTIONS += --enable-man
CONFIGURE_OPTIONS += --disable-glibtest
CONFIGURE_OPTIONS += --disable-papi

CONFIGURE_ENV    += PERL=$(PERL)
CONFIGURE_ENV    += PYTHON=$(PYTHON)

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += gnome/accessibility/at-spi2-atk
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
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
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
