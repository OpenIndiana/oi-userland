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
# Copyright 2017 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dovecot
COMPONENT_VERSION=	2.2.27
COMPONENT_SUMMARY=	Dovecot is an open source IMAP and POP3 email server for Linux/UNIX-like systems.
COMPONENT_PROJECT_URL=	http://dovecot.org
COMPONENT_FMRI=		service/network/imap/dovecot
COMPONENT_CLASSIFICATION= System/Services
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	http://dovecot.org/releases/2.2/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:897f92a87cda4b27b243f8149ce0ba7b7e71a2be8fb7994eb0a025e54cde18e9
COMPONENT_LICENSE=	MIT/LGPL2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=/usr/lib/dovecot
CONFIGURE_OPTIONS += --with-ioloop=poll
CONFIGURE_OPTIONS += --with-sqlite
CONFIGURE_OPTIONS += --with-sql=yes

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
