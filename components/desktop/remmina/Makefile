#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2020 Marco van Wieringen
# Copyright 2023 Niklas Poslovski
#

BUILD_BITS= 64
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		remmina
COMPONENT_VERSION=	1.4.31
COMPONENT_SUMMARY=	Remmina remote desktop client
COMPONENT_PROJECT_URL=	https://remmina.org
COMPONENT_FMRI=		desktop/remote-desktop/remmina
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_SRC_NAME=	Remmina
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:c59444e4f97c26205455b8ad4b7dbffc8dffd24dcef3f4094090f9fa97a5be0d
COMPONENT_ARCHIVE_URL=  https://github.com/FreeRDP/Remmina/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	Apache v2.0
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lnsl -lsocket

CMAKE_OPTIONS += -DWITH_AVAHI=OFF
CMAKE_OPTIONS += -DWITH_LIBSSH=OFF
CMAKE_OPTIONS += -DWITH_APPINDICATOR=OFF
CMAKE_OPTIONS += -DGETTEXT_MSGMERGE_EXECUTABLE=/usr/bin/gmsgmerge
CMAKE_OPTIONS += -DGETTEXT_MSGFMT_EXECUTABLE=/usr/bin/gmsgfmt

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += desktop/library/libayatana-appindicator
REQUIRED_PACKAGES += desktop/remote-desktop/freerdp
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/desktop/webkitgtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/libvncserver
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
