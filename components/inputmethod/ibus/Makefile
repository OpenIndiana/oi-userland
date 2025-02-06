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

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         ibus
COMPONENT_VERSION=      1.5.27
COMPONENT_SUMMARY=      iBus - Intelligent Input Bus
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:6efbda5adb96f607cf7108d1e270962c0729a59c9ea6d58eea2dde0e3cbb97df
COMPONENT_PROJECT_URL=  https://github.com/ibus/ibus
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			system/input-method/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Internationalization
COMPONENT_LICENSE=		LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Force rebuilding C sources from vala sources to avoid Wayland dependencies
# Workaround for https://github.com/ibus/ibus/issues/2609
COMPONENT_POST_UNPACK_ACTION += $(TOUCH) $(SOURCE_DIR)/ui/gtk3/*.vala ;

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_SCRIPT= $(@D)/configure

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-gtk2
CONFIGURE_OPTIONS += --enable-gtk3
CONFIGURE_OPTIONS += --enable-gtk4
CONFIGURE_OPTIONS += --enable-xim
CONFIGURE_OPTIONS += --disable-gtk-doc
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --disable-python2
CONFIGURE_OPTIONS += --disable-emoji-dict
CONFIGURE_OPTIONS += --disable-unicode-dict
CONFIGURE_OPTIONS += --disable-systemd-services
CONFIGURE_OPTIONS += --disable-wayland

CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

# Note: Running the tests need X11 and testing gets stuck at the ibus-compose tests.
# Furhter note that starting with 1.5.28 tests get stuck at ibus-bus tests (the very first tests).
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :1 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:1
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

# Manually added build dependencies
REQUIRED_PACKAGES += data/iso-codes
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/accessibility/at-spi2-core
REQUIRED_PACKAGES += gnome/config/dconf
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxi
