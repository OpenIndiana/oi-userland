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
# Copyright 2011 EveryCity Ltd. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		GeoIP
COMPONENT_VERSION=	1.4.8
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:cf0f6b2bac1153e34d6ef55ee3851479b347d2b5c191fda8ff6a51fab5291ff4
COMPONENT_ARCHIVE_URL=	http://geolite.maxmind.com/download/geoip/api/c/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS +=	--with-pic
CONFIGURE_OPTIONS +=	--no-recursion
CONFIGURE_OPTIONS +=	--enable-libtool-lock
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS)"
CONFIGURE_SCRIPT   =	$(@D)/configure

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D) && \
		cd $(@D) && libtoolize && ./bootstrap )

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

