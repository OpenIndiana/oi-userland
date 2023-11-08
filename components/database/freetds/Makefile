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
# Copyright 2016 Alexander Pyhalov
# Copyright 2018 Michal Nowak
# Copyright 2023 Friedrich Kink
#

OPENSSL_VERSION=	3.1

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		freetds
COMPONENT_VERSION=	1.4.6
COMPONENT_PROJECT_URL=	https://www.freetds.org/
COMPONENT_SUMMARY=	FreeTDS command-line utilities
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c33b051b98cbe8ce9a8ae49074642c567bf64edd08257216fb5cec4e40b3af97
COMPONENT_ARCHIVE_URL=	https://www.freetds.org/files/stable/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		database/freetds
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING.txt

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--enable-krb5
CONFIGURE_OPTIONS +=	--enable-msdblib
CONFIGURE_OPTIONS +=	--with-gnutls

COMPONENT_TEST_ARGS+=   -k
COMPONENT_TEST_TRANSFORMS = \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/XFAIL:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/XPASS:/p" ' \
        '-e "/ERROR:/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/nettle
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
