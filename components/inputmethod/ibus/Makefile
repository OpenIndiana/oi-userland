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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ibus
COMPONENT_VERSION= 1.5.13
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= iBus - Intelligent Input Bus
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:ed73d80542dfdcca190b7958431048cd6830c2ce25c467384630b6a7e957a5f1
COMPONENT_PROJECT_URL = https://github.com/ibus/ibus
COMPONENT_ARCHIVE_URL= \
  $(COMPONENT_PROJECT_URL)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH = $(PATH.gnu)

GTK_BIN_VER := $(shell pkg-config --variable=gtk_binary_version gtk+-2.0)

PKG_MACROS += GTK_BIN_VER=$(GTK_BIN_VER)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))
CONFIGURE_SCRIPT= $(@D)/configure

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-gtk2
CONFIGURE_OPTIONS += --enable-gtk3
CONFIGURE_OPTIONS += --enable-xim
CONFIGURE_OPTIONS += --disable-gtk-doc
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib/ibus
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/ibus/$(MACH64)
CONFIGURE_OPTIONS.64 += --with-gtk-im-module-dir=/usr/lib/$(MACH64)/gtk-2.0/$(GTK_BIN_VER)/immodules/

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

REQUIRED_PACKAGES += gnome/config/dconf
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxi
