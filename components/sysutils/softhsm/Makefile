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

BUILD_BITS= 32_and_64
OPENSSL_VERSION= 3.1
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	 	softhsm
COMPONENT_VERSION=  2.6.1
COMPONENT_REVISION=	3
COMPONENT_PROJECT_URL=  https://www.opendnssec.org/softhsm/
COMPONENT_SUMMARY= 	SoftHSM is an implementation of a cryptographic store accessible through a PKCS11 interface.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:61249473054bcd1811519ef9a989a880a7bdcc36d317c9c25457fc614df475f2
COMPONENT_ARCHIVE_URL=	https://dist.opendnssec.org/source/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		security/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Security
COMPONENT_LICENSE=      BSD

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Provide paths for OpenSSL 3.1
CFLAGS  += -I$(OPENSSL_INCDIR)
LDFLAGS += -L$(OPENSSL_LIBDIR)

# This lets the 32-bit binaries being replaced with its 64-bit counterparts:
CONFIGURE_BINDIR.64= $(CONFIGURE_BINDIR.32)

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --with-crypto-backend=openssl
CONFIGURE_OPTIONS += --with-openssl=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS += --with-migrate
CONFIGURE_OPTIONS += --with-sqlite3=$(USRDIR)

COMPONENT_TEST_TRANSFORMS += \
    '-e "/=========/p" ' \
	'-e "/Testsuite summary for/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += system/library
