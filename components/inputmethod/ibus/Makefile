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

BUILD_BITS=64_and_32

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ibus
COMPONENT_VERSION= 1.5.22
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= iBus - Intelligent Input Bus
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:8170eba58c28aa4818970751ebdeada728ebb63d535967a5c5f5c21b0017be4a
COMPONENT_PROJECT_URL = https://github.com/ibus/ibus
COMPONENT_ARCHIVE_URL= \
  $(COMPONENT_PROJECT_URL)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)
PYTHON_VERSION = 3.5

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
CONFIGURE_OPTIONS.32 += --disable-introspection
CONFIGURE_OPTIONS.64 += --enable-introspection
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib/ibus
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/ibus/$(MACH64)
CONFIGURE_OPTIONS.64 += --with-gtk-im-module-dir=/usr/lib/$(MACH64)/gtk-2.0/$(GTK_BIN_VER)/immodules/
CONFIGURE_OPTIONS += --disable-emoji-dict
CONFIGURE_OPTIONS += --disable-unicode-dict

CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += gnome/config/dconf
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxi
