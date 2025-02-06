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
# Copyright (c) 2015 Alexander Pyhalov
#

BUILD_STYLE = meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xdg-user-dirs-gtk
HUMAN_VERSION=			0.14
COMPONENT_VERSION_MAJOR=	$(HUMAN_VERSION)
COMPONENT_SUMMARY=		Integrates xdg-user-dirs into the Gnome desktop and Gtk+ applications
COMPONENT_ARCHIVE_HASH=		sha256:537fbe142b24736ed7894e4a01f69fd758cb6c7a677a382879529d217f4a2873
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=		GPL-2.0-only
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_FMRI=		desktop/xdg/xdg-user-dirs-gtk

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH=$(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/xdg/xdg-user-dirs
REQUIRED_PACKAGES += system/library
