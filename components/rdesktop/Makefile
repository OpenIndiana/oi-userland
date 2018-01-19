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
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		rdesktop
COMPONENT_VERSION=	1.8.3
COMPONENT_PROJECT_URL=	http://www.rdesktop.org/
COMPONENT_SUMMARY=	RDP, Microsoft Terminal Services client
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:88b20156b34eff5f1b453f7c724e0a3ff9370a599e69c01dc2bf0b5e650eece4
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI=		desktop/remote-desktop/rdesktop
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv3

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--with-ipv6
CONFIGURE_OPTIONS+=	--with-openssl=/usr
CONFIGURE_OPTIONS+=	--disable-credssp
CONFIGURE_OPTIONS+=	--disable-smartcard
CONFIGURE_OPTIONS+=	--with-sound=oss

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libsamplerate
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxrandr
