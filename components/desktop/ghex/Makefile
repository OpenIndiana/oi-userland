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
# Copyright (c) 2024 Geoff Weiss
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         ghex
HUMAN_VERSION=		46.0
COMPONENT_SUMMARY=      Hex editor for the GNOME desktop
COMPONENT_ARCHIVE_HASH=	sha256:a1c46f3020cb358b8323025db3a539c97d994a4c46f701f48edc6357f7fbcbd1
COMPONENT_FMRI=         desktop/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_LICENSE=	GPL-2.0-only
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH= $(PATH.gnu)

# illumos does not have mremap support
CONFIGURE_OPTIONS += -Dmmap-buffer-backend=false

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/libadwaita
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
