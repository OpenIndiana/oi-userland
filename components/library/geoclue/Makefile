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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		geoclue
COMPONENT_VERSION=	2.7.2
COMPONENT_PROJECT_URL=	https://gitlab.freedesktop.org/geoclue/geoclue/-/wikis/home
COMPONENT_SUMMARY=	GeoClue - D-Bus geoinformation service
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:01d24a44a036769049411899ae83c9a86f73d272cca3df6af5a03bfac32456d2
COMPONENT_ARCHIVE_URL=	https://gitlab.freedesktop.org/geoclue/geoclue/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/desktop/geoclue
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	GPL-2.0-or-later AND LGPL-2.1-or-later
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH=			$(PATH.gnu)

CONFIGURE_OPTIONS +=	-Dgtk-doc=false
# no ModemManager (3G, CDMA, modem GPS) and no Avahi (NMEA)
CONFIGURE_OPTIONS +=	-D3g-source=false
CONFIGURE_OPTIONS +=	-Dcdma-source=false
CONFIGURE_OPTIONS +=	-Dmodem-gps-source=false
CONFIGURE_OPTIONS +=	-Dnmea-source=false
CONFIGURE_OPTIONS +=	-Ddemo-agent=false

# The system bus does not activate services: geoclue runs under SMF
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -D -m 0444 $(COMPONENT_DIR)/files/geoclue.xml \
	    $(PROTOLIBDIR)/svc/manifest/system/geoclue.xml ; \
	$(INSTALL) -D -m 0555 $(COMPONENT_DIR)/files/svc-geoclue \
	    $(PROTOLIBDIR)/svc/method/svc-geoclue ;

# vapigen for the vala bindings
REQUIRED_PACKAGES += developer/vala

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsoup3
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += system/library/math
