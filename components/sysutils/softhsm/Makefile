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
# Copyright 2016 Adam Stevko
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	 	softhsm
COMPONENT_VERSION=     	2.1.0
COMPONENT_REVISION=     1
COMPONENT_LICENSE=      BSD
COMPONENT_PROJECT_URL=  https://www.opendnssec.org/softhsm/
COMPONENT_SUMMARY= 	SoftHSM is an implementation of a cryptographic store accessible through a PKCS11 interface.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0399b06f196fbfaebe73b4aeff2e2d65d0dc1901161513d0d6a94f031dcd827e
COMPONENT_ARCHIVE_URL= https://dist.opendnssec.org/source/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_BINDIR.64= $(CONFIGURE_BINDIR.32)

CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --localstatedir=/var
CONFIGURE_OPTIONS+= --disable-ecc
CONFIGURE_OPTIONS+= --with-crypto-backend=botan
CONFIGURE_OPTIONS+= --with-botan=/usr
CONFIGURE_OPTIONS+= --with-migrate
CONFIGURE_OPTIONS+= --with-sqlite3=/usr

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/security/botan
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
