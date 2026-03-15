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
HUMAN_VERSION =			50.0
COMPONENT_SUMMARY =		Collection of GSettings schemas for settings shared by various components of a desktop
COMPONENT_ARCHIVE_HASH =	\
	sha256:358f07cb253727650e132805df3c69f7bf90448040bce171b6f6f2cb1b9c37ef
COMPONENT_FMRI =		gnome/config/gsettings-desktop-schemas
COMPONENT_LICENSE =		LGPL-2.1-only
COMPONENT_LICENSE_FILE =	COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# Manually added build dependencies
REQUIRED_PACKAGES+= library/desktop/gobject/gobject-introspection

# Auto-generated dependencies
