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

# libportal 0.11.0 with the GTK 3 and GTK 4 backends (no Qt). Nautilus 47
# needs it. Without xdg-desktop-portal the portal calls simply fail;
# Nautilus works without them.

BUILD_BITS=		64
BUILD_STYLE=		meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libportal
HUMAN_VERSION=		0.11.0
COMPONENT_SUMMARY=	libportal - GIO-style async API for the XDG desktop portals
COMPONENT_PROJECT_URL=	https://github.com/flatpak/libportal
COMPONENT_ARCHIVE_HASH=	\
	sha256:abb9e452a1c372133bd3eb8f0bb30d07b2d0a8fb02001c4155cf287555db4040
COMPONENT_FMRI=		library/desktop/libportal
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPL-3.0-only
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

TEST_TARGET=		$(NO_TESTS)

COMPONENT_ARCHIVE_URL=	https://github.com/flatpak/libportal/releases/download/$(HUMAN_VERSION)/libportal-$(HUMAN_VERSION).tar.xz
include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

CFLAGS +=		-D__EXTENSIONS__ -D_POSIX_PTHREAD_SEMANTICS
# per-thread errno on illumos (GLib programs are threaded)
CFLAGS +=		-D_REENTRANT

CONFIGURE_OPTIONS +=	--libexecdir=$(USRLIBEXECDIR)
CONFIGURE_OPTIONS +=	-Dbackend-gtk3=enabled
CONFIGURE_OPTIONS +=	-Dbackend-gtk4=enabled
CONFIGURE_OPTIONS +=	-Dbackend-qt5=disabled
CONFIGURE_OPTIONS +=	-Dbackend-qt6=disabled
CONFIGURE_OPTIONS +=	-Ddocs=false
CONFIGURE_OPTIONS +=	-Dtests=false
CONFIGURE_OPTIONS +=	-Dvapi=false

CONFIGURE_ENV +=	PATH="$(GNUBIN):$(PATH)"

REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
