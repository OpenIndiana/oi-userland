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

BUILD_STYLE= cmake
USE_PARALLEL_BUILD = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Remmina
COMPONENT_VERSION=	1.4.39
COMPONENT_SUMMARY=	Remmina remote desktop client
COMPONENT_PROJECT_URL=	https://remmina.org
COMPONENT_FMRI=		desktop/remote-desktop/remmina
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:33cd3347226a1a7df05d74f0336b3da3bb34119a8809ccc9677c15a192ee401d
COMPONENT_ARCHIVE_URL=  https://github.com/FreeRDP/Remmina/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	GPL-2.0-or-later WITH cryptsetup-OpenSSL-exception
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Remmina expects to find libsocket functions in libc
LDFLAGS += -lsocket

CMAKE_OPTIONS += -DWITH_AVAHI=OFF
CMAKE_OPTIONS += -DWITH_LIBSSH=OFF
CMAKE_OPTIONS += -DWITH_APPINDICATOR=OFF
CMAKE_OPTIONS += -DGETTEXT_MSGMERGE_EXECUTABLE=/usr/bin/gmsgmerge
CMAKE_OPTIONS += -DGETTEXT_MSGFMT_EXECUTABLE=/usr/bin/gmsgfmt

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
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
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += web/curl
