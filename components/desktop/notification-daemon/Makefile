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
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		notification-daemon
COMPONENT_VERSION=	0.4.0
COMPONENT_REVISION=	4
COMPONENT_PROJECT_URL=	http://www.galago-project.org/news/index.php
COMPONENT_SUMMARY=	Window Navigator Construction Kit Library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:29aaf4ed090589e69ca5dbbb9125a27c9a194e535cb3b96d26e95bd80ffea530
COMPONENT_ARCHIVE_URL=	http://www.galago-project.org/files/releases/source/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH = $(PATH.gnu)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS+=	--disable-static

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += gnome/gnome-panel

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libglade
REQUIRED_PACKAGES += library/desktop/libsexy
REQUIRED_PACKAGES += library/desktop/libwnck
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += x11/library/libx11
