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

BUILD_STYLE=		meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libportal
HUMAN_VERSION=		0.11.0
COMPONENT_SUMMARY=	libportal - GIO-style async API for the XDG desktop portals
COMPONENT_PROJECT_URL=	https://github.com/flatpak/libportal
COMPONENT_ARCHIVE_HASH=	\
	sha256:abb9e452a1c372133bd3eb8f0bb30d07b2d0a8fb02001c4155cf287555db4040
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/download/$(HUMAN_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/desktop/libportal
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	LGPL-3.0-only
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# per-thread errno
CFLAGS +=		-D_REENTRANT

CONFIGURE_OPTIONS +=	-Dbackend-qt5=disabled
CONFIGURE_OPTIONS +=	-Dbackend-qt6=disabled
CONFIGURE_OPTIONS +=	-Ddocs=false
CONFIGURE_OPTIONS +=	-Dtests=false
CONFIGURE_OPTIONS +=	-Dvapi=false

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
