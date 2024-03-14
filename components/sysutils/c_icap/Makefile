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
# Copyright 2022,2023 Friedrich Kink. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		c_icap
COMPONENT_VERSION=	0.6.2
COMPONENT_SUMMARY=	The c-icap project
COMPONENT_DESCRIPTION=	c-icap is an implementation of an ICAP server. It can be \
			used with HTTP proxies that support the ICAP protocol to \
			implement content adaptation and filtering services. \
			Most of the commercial HTTP proxies must support the ICAP \
			protocol. The open source Squid 3.x proxy server supports it. 
COMPONENT_SRC=		c-icap-server-C_ICAP_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	C_ICAP_$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:6c297a0f20501ab3b7356473ac66802bd8b866735e0aa6f999f90facaa4aeed9
COMPONENT_PROJECT_URL=	https://c-icap.sourceforge.net/
COMPONENT_ARCHIVE_URL=	https://github.com/c-icap/c-icap-server/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= 	antivirus/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CXXFLAGS += -std=c++11

COMPONENT_PREP_ACTION=( cd $(@D) && PATH="$(PATH)" autoreconf -f -i -v -W all )

CONFIGURE_OPTIONS += CPPFLAGS=-I/usr/include/openldap
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-dependency-tracking

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += database/lmdb
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/libmemcached
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
