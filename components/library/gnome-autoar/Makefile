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

# gnome-autoar 0.4.5 (archive helper library; gnome-shell 45 needs it), as in
# Solaris 11.4 (solaris-userland components/gnome/gnome-autoar @9d7a655),
# without vala bindings and docs.

BUILD_BITS=		64
BUILD_STYLE=		meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-autoar
HUMAN_VERSION=		0.4.5
COMPONENT_SUMMARY=	gnome-autoar - archive integration helpers for GNOME
COMPONENT_ARCHIVE_HASH=	\
	sha256:838c5306fc38bfaa2f23abe24262f4bf15771e3303fb5dcb74f5b9c7a615dabe
COMPONENT_FMRI=		library/desktop/gnome-autoar
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPL-2.1-or-later
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=	-Dgtk_doc=false
CONFIGURE_OPTIONS +=	-Dtests=false
CONFIGURE_OPTIONS +=	-Dvapi=false
CONFIGURE_OPTIONS +=	-Dintrospection=enabled

CONFIGURE_ENV +=	PATH="$(GNUBIN):$(PATH)"

REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += system/library
