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
# Copyright (c) 2018 Alexander Pyhalov
# Copyright (c) 2019 Michal Nowak
#

BUILD_BITS=		64

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mate-power-manager
COMPONENT_MJR_VERSION=  1.22
COMPONENT_MNR_VERSION=  2
COMPONENT_REVISION=	1
COMPONENT_VERSION=      $(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_PROJECT_URL=  http://www.mate-desktop.org
COMPONENT_SUMMARY=      MATE Power Manager utilities for desktop users
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:76d1ce28b812ba0fd118d5aa529538072cef1336ae76aea1832ecc00fc91f68a
COMPONENT_ARCHIVE_URL=  http://pub.mate-desktop.org/releases/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		desktop/mate/mate-power-manager
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION =        ( cd $(@D) && autoreconf -fi )

CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib/mate
CONFIGURE_OPTIONS+=	--sysconfdir=/etc
# Needs library/gnome/gnome-keyring >= 3.0.0
CONFIGURE_OPTIONS+=	--without-keyring

CONFIGURE_ENV+= PYTHON="$(PYTHON)"
CONFIGURE_ENV+= PERL="$(PERL)"

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/mate/mate-panel
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/upower
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrandr
