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
# Copyright 2022, Friedrich Kink. All rights reserved.
#

BUILD_BITS=             64
BUILD_STYLE=            configure

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		c_icap
COMPONENT_VERSION=	0.5.10
COMPONENT_SUMMARY=	ClamAV $(IPS_COMPONENT_VERSION) opensource antivirus toolkit
COMPONENT_FMRI= 	antivirus/$(COMPONENT_NAME)
COMPONENT_DESCRIPTION=	c-icap is an implementation of an ICAP server. It can be \
			used with HTTP proxies that support the ICAP protocol to \
			implement content adaptation and filtering services. \
			Most of the commercial HTTP proxies must support the ICAP \
			protocol. The open source Squid 3.x proxy server supports it. 
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:541d503354907f06d1d72fa90fffd031002f0f4346150fb7b2203ad5825ae49d
COMPONENT_PROJECT_URL=	http://c-icap.sourceforge.net/
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/c-icap/files/c-icap/0.5.x/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+=     CPPFLAGS=-I/usr/include/openldap
CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-dependency-tracking

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/libmemcached
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
