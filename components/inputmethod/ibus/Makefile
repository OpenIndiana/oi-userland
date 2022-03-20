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

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ibus
COMPONENT_VERSION= 1.5.26
COMPONENT_SUMMARY= iBus - Intelligent Input Bus
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:5c2fd118e7bfd4e9a42c3a20e6175a263426c90b6256f94989ed3d0384f4c9fc
COMPONENT_PROJECT_URL=	https://github.com/ibus/ibus
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)
PYTHON_VERSION = 3.9

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
CONFIGURE_OPTIONS += --disable-systemd-services

CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

# Note: Running the tests need X11.
unexport SHELLOPTS

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
         '-n ' \
         '-e "/^PASS:/p" ' \
         '-e "/^XPASS:/p" ' \
         '-e "/^ERROR:/p" ' \
         '-e "/^FAIL:/p" ' \
         '-e "/^XFAIL:/p" ' \
         '-e "/^SKIP:/p" ' \
         '-e "/^TOTAL:/p" ' \
         '-e "/^See/p" ' \
         '-e "/^Please/p" ' \
         '-e "/^Testsuite/p" ' \
         '-e "/====/p" '

# Manually added build dependencies
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += runtime/python-39

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/config/dconf
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxi
