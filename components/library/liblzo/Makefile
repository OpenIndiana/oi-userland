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
# Copyright 2012 EveryCity Ltd. All rights reserved.
# Copyright 2013 Adam Stevko. All rights reserved.
# Copyright 2016 Jim Klimov. All rights reserved.
# Copyright 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		lzo
COMPONENT_VERSION=	2.10
IPS_COMPONENT_VERSION=	2.0.10
COMPONENT_FMRI=		library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION =	System/Libraries
COMPONENT_SUMMARY=	LZO is a portable lossless data compression library written in ANSI C
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:c0f892943208266f9b6543b3ae308fab6284c5c90e627931446fb49b4221a072
COMPONENT_PROJECT_URL=	http://www.oberhumer.com/opensource/$(COMPONENT_NAME)/
COMPONENT_ARCHIVE_URL=	http://www.oberhumer.com/opensource/$(COMPONENT_NAME)/download/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS+=	--enable-static=no
CONFIGURE_OPTIONS+=	--enable-shared

COMPONENT_TEST_TARGETS =	check test

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
