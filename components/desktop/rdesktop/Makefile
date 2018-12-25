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
# Copyright 2018 Alexander Pyhalov
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rdesktop
COMPONENT_VERSION=	1.8.3
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.rdesktop.org/
COMPONENT_SUMMARY=	RDP, Microsoft Terminal Services client
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=	\
    sha256:e8e4cab3a84ee8b73ed77ef11183d19403920ab7b6d8325b24dab8da7bbd123d
COMPONENT_COMMIT=	1f13bf5c5e86cbc99a6f0492fcdcd38cf0da2105
COMPONENT_ARCHIVE_URL=	https://github.com/rdesktop/rdesktop/archive/$(COMPONENT_COMMIT).zip
COMPONENT_FMRI=		desktop/remote-desktop/rdesktop
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv3

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -if)

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--with-ipv6
CONFIGURE_OPTIONS+=	--with-openssl=/usr
CONFIGURE_OPTIONS+=	--enable-credssp
CONFIGURE_OPTIONS+=	--disable-smartcard
CONFIGURE_OPTIONS+=	--with-sound=oss

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libsamplerate
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxrandr
