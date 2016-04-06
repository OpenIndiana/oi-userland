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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ibus
COMPONENT_VERSION= 1.3.9
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= iBus - Intelligent Input Bus
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:b2784a668666efa8ae04e6f1cff5749917cd18add0a39a1d020ecc9f3df5285d
COMPONENT_ARCHIVE_URL= \
  http://ibus.googlecode.com/files/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://code.google.com/p/ibus/

CONFIGURE_SYSCONFDIR.32 = $(ETCDIR)
CONFIGURE_SYSCONFDIR.64 = $(ETCDIR)/$(MACH64)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

gcc_OPT = -O2

PATH = /usr/gnu/bin:/usr/bin

GTK_BIN_VER := $(shell pkg-config --variable=gtk_binary_version gtk+-2.0)

PKG_MACROS += GTK_BIN_VER=$(GTK_BIN_VER)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))
CONFIGURE_SCRIPT= $(@D)/configure

CONFIGURE_LIBEXECDIR.32 = $(CONFIGURE_LIBDIR.32)/ibus
CONFIGURE_LIBEXECDIR.64 = $(CONFIGURE_LIBEXECDIR.32)/$(MACH64)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-gtk2
CONFIGURE_OPTIONS += --enable-xim
CONFIGURE_OPTIONS += --disable-gtk-doc
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS.64 += --with-gtk-im-module-dir=$(USRLIBDIR64)/gtk-2.0/$(GTK_BIN_VER)/immodules/

CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

$(INSTALL_32):  $(INSTALL_64)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += x11/library/libx11
