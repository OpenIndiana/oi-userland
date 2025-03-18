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
# Copyright 2024 Geoff Weiss
#

BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libadwaita
HUMAN_VERSION=		1.6.5
COMPONENT_SUMMARY=	Building blocks for modern GNOME applications.
COMPONENT_ARCHIVE_HASH=	sha256:d4713cfe5daeb2e537ccb6cb013c153677a3f1c29e5c166c5663e33605eb8ee2
COMPONENT_PROJECT_URL=	https://gnome.pages.gitlab.gnome.org/libadwaita/doc/
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_FMRI=		library/desktop/libadwaita

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH=$(PATH.gnu)

# Some warnings are treated as errors by default but we do not want that
# see https://gitlab.gnome.org/GNOME/libadwaita/-/issues/985
CFLAGS += -Wno-error=format-nonliteral

# Testing needs an X server
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :0 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:0
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

# Build dependencies
REQUIRED_PACKAGES += developer/sassc

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/appstream
REQUIRED_PACKAGES += library/desktop/graphene
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
