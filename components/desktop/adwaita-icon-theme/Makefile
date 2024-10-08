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
# Copyright 2018 Michal Nowak
# Copyright 2020 Andreas Wacknitz
#

BUILD_STYLE = meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			adwaita-icon-theme
HUMAN_VERSION=			47.0
COMPONENT_SUMMARY=		GNOME Icon Theme
COMPONENT_ARCHIVE_HASH=		sha256:ad088a22958cb8469e41d9f1bba0efb27e586a2102213cd89cc26db2e002bdfe
COMPONENT_FMRI=			gnome/theme/adwaita-icon-theme
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Theming
COMPONENT_LICENSE=		LGPL-3.0-only OR CC-BY-SA-3.0
COMPONENT_LICENSE_FILE=		COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# Build dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf

# Auto-generated dependencies
