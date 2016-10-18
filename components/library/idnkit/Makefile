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

COMPONENT_NAME=		idnkit
COMPONENT_VERSION=	1.0
COMPONENT_SUMMARY=	Provides functionalities about Internationalized Domain Name processing
COMPONENT_PROJECT_URL=	http://www.nic.ad.jp/ja/idn/idnkit
COMPONENT_FMRI=		library/idnkit
COMPONENT_CLASSIFICATION= System/Internationalization
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://www.nic.ad.jp/ja/idn/idnkit/download/sources/idnkit-1.0-src.tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:16cd5fce81a5180d6a2c61cf20572668b3dc59f5c39c272b75fa98edab3391fc
COMPONENT_LICENSE=	BSD

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS= --prefix=$(USRDIR)
CONFIGURE_OPTIONS+= --sysconfdir=$(ETCDIR)/$(COMPONENT_NAME)
CONFIGURE_OPTIONS+= --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS+= --libdir=$(CONFIGURE_LIBDIR.$(BITS))

COMPONENT_PRE_CONFIGURE_ACTION= \
	$(CLONEY) $(SOURCE_DIR) $(@D)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += system/library
