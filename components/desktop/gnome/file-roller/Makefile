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

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		file-roller
HUMAN_VERSION=		44.7
COMPONENT_SUMMARY=	File Roller - GNOME archive manager
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/FileRoller
COMPONENT_ARCHIVE_HASH=	\
	sha256:67cada96a2409c859f378e82fbe868b0e9c00a69e6b7b885d542c64ea2a1297d
COMPONENT_FMRI=		desktop/archive-manager/file-roller
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPL-2.0-or-later
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is expected
PATH=			$(PATH.gnu)

# packagekit defaults to true: a D-Bus client that offers to install missing
# archivers through PackageKit, which OpenIndiana does not have
CONFIGURE_OPTIONS +=	-Dpackagekit=false
# no Nautilus extension
CONFIGURE_OPTIONS +=	-Dnautilus-actions=disabled
CONFIGURE_OPTIONS +=	-Dlibarchive=enabled

# update-desktop-database (meson.build requires it)
REQUIRED_PACKAGES += library/desktop/desktop-file-utils

ifeq ($(MACH),sparc)
# file-roller links libm on SPARC only (gmake REQUIRED_PACKAGES runs on x86)
REQUIRED_PACKAGES += system/library/math
endif

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/desktop/libadwaita
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += system/library
