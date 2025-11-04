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
# Copyright 2023 Friedrich Kink.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         clutter
COMPONENT_VERSION=      1.26.4
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=      clutter - a library for creating fast, visually rich and animated graphical user interfaces
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Projects/Clutter
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:8b48fac159843f556d0a6be3dbfc6b083fc6d9c58a20a49a6b4919ab4263c4e6
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/1.26/$(COMPONENT_ARCHIVE)

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CFLAGS+=	-I$(@D)/mesa
CXXFLAGS+=	-I$(@D)/mesa
LDFLAGS.64 =	-L/usr/lib/mesa/$(MACH64) -L/usr/X11/lib/$(MACH64) -R/usr/X11/lib/$(MACH64) -lX11

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-egl-backend=no
CONFIGURE_OPTIONS += --enable-gtk-doc

# Tell g-ir-scanner about compiler
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

# Manually added dependencies
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/accessibility/at-spi2-core
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/cogl
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxi
