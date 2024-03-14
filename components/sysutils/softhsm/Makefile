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
# Softhsm needs some RSA and DSA functions that are not available in openssl-1.1:
#USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	 	softhsm
COMPONENT_VERSION=  2.6.1
COMPONENT_REVISION=	2
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

# This lets the 32-bit binaries being replaced with its 64-bit counterparts:
CONFIGURE_BINDIR.64= $(CONFIGURE_BINDIR.32)

CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --localstatedir=/var
CONFIGURE_OPTIONS+= --with-crypto-backend=openssl
#CONFIGURE_OPTIONS+= --with-openssl=/usr/openssl/1.1
CONFIGURE_OPTIONS+= --with-migrate
CONFIGURE_OPTIONS+= --with-sqlite3=/usr

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/=========/p" ' \
        '-e "/Testsuite summary for/p" ' \
        '-e "/TOTAL/p" ' \
        '-e "/PASS/p" ' \
        '-e "/SKIP/p" ' \
        '-e "/XFAIL/p" ' \
        '-e "/FAIL/p" ' \
        '-e "/XPASS/p" ' \
        '-e "/ERROR/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
