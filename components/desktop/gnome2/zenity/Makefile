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

BUILD_STYLE=configure
BUILD_BITS=64
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=         zenity
COMPONENT_VERSION=      2.32.1
COMPONENT_REVISION=     3
COMPONENT_PROJECT_URL=  http://www.gnome.org
COMPONENT_SUMMARY=      GNOME graphical dialog box generator
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:8838be041a07364b62a4281c971392e4a09bb01bb3237a836ec0457ec0ea18ac
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/2.32/$(COMPONENT_ARCHIVE)

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

LDFLAGS += -lX11

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-scrollkeeper

# Build dependencies
REQUIRED_PACKAGES += developer/gnome/gnome-doc-utils

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
