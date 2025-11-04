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
# Copyright 2017 Gary Mills
# Copyright (c) 2014 Alexander Pyhalov. All rights reserved
#

BUILD_STYLE = meson

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=         zenity
COMPONENT_VERSION=      3.44.5
COMPONENT_SUMMARY=      GNOME graphical dialog box generator
COMPONENT_ARCHIVE_HASH= \
	sha256:29ac447f4246b1da783a3c28ddc80b0ef7c80eccd5836ad9140abf89841d0eab
COMPONENT_FMRI=		gnome/zenity
COMPONENT_CLASSIFICATION=Development/GNOME and GTK+
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU gettext is needed
PATH = $(PATH.gnu)

CONFIGURE_OPTIONS += -Dlibnotify=true
CONFIGURE_OPTIONS += -Dwebkitgtk=true

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/webkitgtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
