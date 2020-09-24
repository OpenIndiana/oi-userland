#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libchamplain
COMPONENT_VERSION=	0.8.3
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	http://projects.gnome.org/libchamplain/
COMPONENT_SUMMARY=	libchamplain - a Clutter based widget to display rich, eye-candy and interactive maps
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:70d533be213a1586d6725d82afb128d1e57ccc262681dfda193af60507ad42e3
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/0.8/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--enable-introspection=no
CONFIGURE_OPTIONS+=	--disable-static

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/clutter
REQUIRED_PACKAGES += library/desktop/clutter/clutter-gtk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
