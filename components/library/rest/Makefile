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
# Copyright 2017 Alexander Pyhalov
#

BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS= yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= rest
HUMAN_VERSION=			0.9.1
COMPONENT_SUMMARY= A library designed to make it easier to access web services that claim to be 'RESTful'
COMPONENT_ARCHIVE_HASH=		sha256:9266a5c10ece383e193dfb7ffb07b509cc1f51521ab8dad76af96ed14212c2e3
COMPONENT_PROJECT_URL=		https://gitlab.gnome.org/GNOME/librest
COMPONENT_FMRI= library/desktop/librest
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		LGPL-2.1-only
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH=$(PATH.gnu)

# Manually added dependency
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/gtksourceview-5
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/desktop/libadwaita
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsoup3
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
