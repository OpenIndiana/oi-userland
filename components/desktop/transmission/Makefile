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
# Copyright 2015 Alexander Pyhalov
# Copyright 2018 Michal Nowak
# Copyright 2022-2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		transmission
COMPONENT_VERSION=	3.0.0
HUMAN_VERSION=		3.00
COMPONENT_REVISION=	3
COMPONENT_PROJECT_URL=	https://www.transmissionbt.com/
COMPONENT_SUMMARY=	GTK and console BitTorrent client
COMPONENT_FMRI=		desktop/torrent/transmission
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:9144652fe742f7f7dd6657716e378da60b751aaeda8bef8344b3eefc4db255f2
COMPONENT_ARCHIVE_URL=	https://github.com/transmission/transmission-releases/raw/master/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2,MIT

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CFLAGS += -Wno-incompatible-pointer-types

CONFIGURE_OPTIONS+=	--program-prefix=""
CONFIGURE_OPTIONS+=	--with-gtk
CONFIGURE_OPTIONS+=	--enable-cli
CONFIGURE_OPTIONS+=	--enable-daemon
CONFIGURE_OPTIONS+=	--enable-utp
CONFIGURE_OPTIONS+=	--with-crypto=openssl
CONFIGURE_OPTIONS+=	--disable-static

COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/TOTAL|PASS|FAIL|XFAIL|SKIP|XPASS|ERROR/'"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
