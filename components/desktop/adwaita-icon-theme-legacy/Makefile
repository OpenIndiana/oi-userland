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
# Copyright 2024 Marcel Telka
#

BUILD_STYLE = meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			adwaita-icon-theme-legacy
HUMAN_VERSION=			46.2
COMPONENT_SUMMARY=		A fullcolor icon theme providing fallback for legacy apps
COMPONENT_ARCHIVE_HASH=		sha256:548480f58589a54b72d18833b755b15ffbd567e3187249d74e2e1f8f99f22fb4
COMPONENT_FMRI=			gnome/theme/adwaita-icon-theme-legacy
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Theming
COMPONENT_LICENSE=		LGPL-3.0-only OR CC-BY-SA-3.0
COMPONENT_LICENSE_FILE=		COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# Build dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf

# Auto-generated dependencies
