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

COMPONENT_NAME=		baobab
HUMAN_VERSION=		47.0
COMPONENT_SUMMARY=	Disk Usage Analyzer for GNOME
COMPONENT_PROJECT_URL=	https://apps.gnome.org/Baobab/
COMPONENT_ARCHIVE_HASH=	\
	sha256:b88f74f9c052d3c2388f7062d228cf5e927545acf7408c56841df80ccd1f9c37
COMPONENT_FMRI=		gnome/disk-analyzer/baobab
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPL-2.0-or-later
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is expected
PATH=			$(PATH.gnu)

# update-desktop-database (meson.build requires it)
REQUIRED_PACKAGES += library/desktop/desktop-file-utils
# baobab is written in Vala
REQUIRED_PACKAGES += developer/vala

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/graphene
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/libadwaita
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
