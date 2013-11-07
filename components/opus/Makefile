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
# Copyright 2013 EveryCity Ltd. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		opus
COMPONENT_VERSION=      1.0.2
COMPONENT_LICENSE=      BSD
COMPONENT_PROJECT_URL=  http://opus-codec.org/
COMPONENT_SUMMARY=	Opus is an open, royalty-free, versatile audio codec for interactive speech and music transmission over the Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:da615edbee5d019c1833071d69a4782c19f178cf9ca1401375036ecef25cd78a
COMPONENT_ARCHIVE_URL=	http://downloads.xiph.org/releases/opus/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS  +=	--disable-static
CONFIGURE_OPTIONS  +=	--enable-shared

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

