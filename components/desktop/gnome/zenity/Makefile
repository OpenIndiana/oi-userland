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
COMPONENT_VERSION=      3.44.3
COMPONENT_VERSION_MAJOR=$(subst $(space),.,$(wordlist 1,2,$(subst ., ,$(COMPONENT_VERSION))))
COMPONENT_PROJECT_URL=  http://www.gnome.org
COMPONENT_SUMMARY=      GNOME graphical dialog box generator
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:86f8c8c51f2bbfc729d4e863a135122de400cbfb3fa43b64b4438790de778c7b
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MAJOR)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		gnome/zenity
COMPONENT_CLASSIFICATION=Development/GNOME and GTK+
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# GNU gettext is needed
PATH = $(PATH.gnu)

CONFIGURE_OPTIONS += -Dlibnotify=true
CONFIGURE_OPTIONS += -Dwebkitgtk=true

# Build dependencies
REQUIRED_PACKAGES += developer/gnome/gnome-doc-utils

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
