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

COMPONENT_NAME=		libspelling
HUMAN_VERSION=		0.4.11
COMPONENT_SUMMARY=	libspelling - spellcheck library for GTK 4
COMPONENT_ARCHIVE_HASH=	\
	sha256:52e53ec3fba0f604cfd0931e26af7f7241a0d4f0208dd5574f43b3589f6d28b2
COMPONENT_FMRI=		library/desktop/libspelling
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPL-2.1-or-later
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=	-Dsysprof=false
CONFIGURE_OPTIONS +=	-Ddocs=false
CONFIGURE_OPTIONS +=	-Dvapi=false

# Auto-generated dependencies
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/gtksourceview-5
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += system/library
