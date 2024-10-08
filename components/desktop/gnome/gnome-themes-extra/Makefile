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
# Copyright 2024 Marcel Telka
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=			gnome-themes-extra
HUMAN_VERSION=			3.28
COMPONENT_VERSION_MAJOR=	$(HUMAN_VERSION)
COMPONENT_SUMMARY=		GNOME Extra Themes
COMPONENT_ARCHIVE_HASH= \
	sha256:7c4ba0bff001f06d8983cfc105adaac42df1d1267a2591798a780bac557a5819
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Theming
COMPONENT_FMRI=			gnome/theme/$(COMPONENT_NAME)
COMPONENT_LICENSE=		LGPL-2.1-only
COMPONENT_LICENSE_FILE=		LICENSE

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU xgettext is needed
PATH=$(PATH.gnu)

# Manually added build dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
