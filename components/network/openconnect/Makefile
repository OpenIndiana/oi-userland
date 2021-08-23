#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Jim Klimov
# Copyright 2019 Michal Nowak
# Copyright 2020 Andreas Wacknitz
#

BUILD_BITS=		64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openconnect
COMPONENT_VERSION=	8.10
COMPONENT_REVISION=	2
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://www.infradead.org/openconnect
COMPONENT_ARCHIVE_HASH=	sha256:ae99d87585388098510c837e3db5f0a9ad13998464a91bd30275de58c0c995f3
COMPONENT_ARCHIVE_URL=	https://github.com/openconnect/openconnect/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING.LGPL
COMPONENT_SUMMARY=	An SSL VPN client (intended to be) compatible with Cisco AnyConnect and Juniper Pulse

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = \
	(cd $(@D) && \
	autoreconf -fiv && \
	$(RM) config.h )

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# To prevent "libtool_install_magic: unbound variable"
unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS= \
    '-n ' \
    '-e "/TOTAL/p" ' \
    '-e "/PASS/p" '  \
    '-e "/SKIP/p" '  \
    '-e "/XFAIL/p" ' \
    '-e "/FAIL/p" '  \
    '-e "/XPASS/p" ' \
    '-e "/ERROR/p" '

OPENSSL_VERSION = 1.1
# Use OpenSSL, it allows more options on OI/Hipster that openconnect uses
CONFIGURE_OPTIONS +=	--with-system-cafile=/etc/certs/ca-certificates.crt
CONFIGURE_OPTIONS +=	--without-gnutls
CONFIGURE_OPTIONS +=	--libexecdir=/usr/lib/$(MACH64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += network/vpnc-scripts
REQUIRED_PACKAGES += driver/network/header-tun

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libproxy
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/lz4
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
