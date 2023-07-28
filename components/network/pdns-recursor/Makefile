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
# Copyright 2016 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
# Copyright 2023 Klaus Ziegler
# Copyright 2023 Niklas Poslovski
#

USE_OPENSSL11=yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pdns-recursor
COMPONENT_VERSION=	4.9.0
COMPONENT_PROJECT_URL=	https://www.powerdns.com/downloads.html
COMPONENT_FMRI=		service/network/dns/powerdns-recursor
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:d36f162843e367646a661a785ca0becde9b68552855bf40532aebafa103966f3
COMPONENT_ARCHIVE_URL=	https://downloads.powerdns.com/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_SUMMARY=	a DNS server
COMPONENT_CLASSIFICATION=System/Services

include $(WS_MAKE_RULES)/common.mk

CXXFLAGS+=-g -pthread

COMPONENT_PREP_ACTION += (cd $(@D) && autoreconf -fi)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS += ac_cv_func_EVP_MD_CTX_new=yes
CONFIGURE_OPTIONS += ac_cv_func_EVP_MD_CTX_free=yes
CONFIGURE_OPTIONS += --sysconfdir=/etc/powerdns
CONFIGURE_OPTIONS += --with-lua
CONFIGURE_OPTIONS += --enable-reproducible
CONFIGURE_OPTIONS += --enable-unit-tests

COMPONENT_TEST_TRANSFORMS = $(CONFIGURE_TEST_TRANSFORMS)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/boost
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += web/curl
