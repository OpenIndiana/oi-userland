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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pdns-recursor
COMPONENT_VERSION=	4.0.8
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://www.powerdns.com/downloads.html
COMPONENT_FMRI=		service/network/dns/powerdns-recursor
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:9c6ff00f0e26044b0c81f1a8304743b4fc0f6699a356fce28cc8c2e6aaf16513
COMPONENT_ARCHIVE_URL=	http://downloads.powerdns.com/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	a DNS server
COMPONENT_CLASSIFICATION="System/Services"

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CXXFLAGS+=-g -pthread

COMPONENT_PREP_ACTION += (cd $(@D) && autoreconf -fi)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS += --sysconfdir=/etc/powerdns
CONFIGURE_OPTIONS += --without-luajit
CONFIGURE_OPTIONS += --with-lua
CONFIGURE_OPTIONS += --enable-reproducible


build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/c++/protobuf
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/lua-53
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/boost
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
