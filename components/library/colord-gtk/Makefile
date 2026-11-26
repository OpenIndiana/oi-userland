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
# Copyright 2026 isoriano1968
#

# colord-gtk 0.3.1 (GTK widgets for colord; gnome-control-center's Color
# panel), as in Solaris 11.4 (solaris-userland components/desktop/colord-gtk
# @9d7a655) with its patch, 64-bit, GTK 3 and GTK 4, no vala bindings.

BUILD_BITS=		64
BUILD_STYLE=		meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		colord-gtk
COMPONENT_VERSION=	0.3.1
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/software/colord/
COMPONENT_SUMMARY=	colord-gtk - GTK integration for colord
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:c176b889b75630a17f4e3d7ef24c09a3e12368e633496087459c8b53ac3a122d
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/desktop/colord-gtk
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPL-2.1-or-later
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=	-Dgtk2=false
CONFIGURE_OPTIONS +=	-Dgtk3=true
CONFIGURE_OPTIONS +=	-Dgtk4=true
CONFIGURE_OPTIONS +=	-Dman=false
CONFIGURE_OPTIONS +=	-Dintrospection=true
CONFIGURE_OPTIONS +=	-Dvapi=false
CONFIGURE_OPTIONS +=	-Ddocs=false
CONFIGURE_OPTIONS +=	-Dtests=false

CONFIGURE_ENV +=	PATH="$(GNUBIN):$(PATH)"

REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += service/image/colord
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += library/desktop/cairo
