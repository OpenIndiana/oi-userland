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
# Copyright 2017 Geoffrey Weiss
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gtksourceview
COMPONENT_MAJOR_MINOR=	3.14
COMPONENT_VERSION=	$(COMPONENT_MAJOR_MINOR).4
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Multiline text editing library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Apps/
COMPONENT_ARCHIVE_URL= \
  https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_MINOR)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
	sha256:1c9d6155705d50ae5cd1cd61167cc4824e413896f10d30ee158a83e8961a4d8b
COMPONENT_FMRI = library/desktop/gtksourceview3
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Documentation
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += GI_SCANNER_DISABLE_CACHE=""

# configure generally requires GNU make explicitly.
CONFIGURE_ENV += MAKE=$(MAKE)

CONFIGURE_ENV += INTLTOOL_PERL="$(PERL)"

CONFIGURE_OPTIONS += --libexecdir=/usr/lib
CONFIGURE_OPTIONS += --localstatedir=/var/lib
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic
# likely requires more fresh vala
CONFIGURE_OPTIONS += --disable-vala

build:	$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Require X11
test:	$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
