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

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME =		gsettings-desktop-schemas
HUMAN_VERSION =			47.1
COMPONENT_SUMMARY =		Collection of GSettings schemas for settings shared by various components of a desktop
COMPONENT_ARCHIVE_HASH =	\
	sha256:a60204d9c9c0a1b264d6d0d134a38340ba5fc6076a34b84da945d8bfcc7a2815
COMPONENT_FMRI =		gnome/config/gsettings-desktop-schemas
COMPONENT_LICENSE =		LGPL-2.1-only
COMPONENT_LICENSE_FILE =	COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# Manually added build dependencies
REQUIRED_PACKAGES+= library/desktop/gobject/gobject-introspection

# Auto-generated dependencies
