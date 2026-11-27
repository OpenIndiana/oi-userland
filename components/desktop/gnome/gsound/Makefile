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

COMPONENT_NAME=		gsound
HUMAN_VERSION=		1.0.3
COMPONENT_SUMMARY=	GSound - GObject library for playing system sounds
COMPONENT_ARCHIVE_HASH=	\
	sha256:ca2d039e1ebd148647017a7f548862350bc9af01986d39f10cfdc8e95f07881a
COMPONENT_FMRI=		library/desktop/gsound
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPL-2.1-or-later
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# vapigen for the vala bindings
REQUIRED_PACKAGES += developer/vala

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
