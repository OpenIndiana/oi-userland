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
# Copyright 2011, 2013, EveryCity Ltd. All rights reserved.
# Copyright 2013, Adam Stevko, All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		nasm
COMPONENT_VERSION=	2.09.10
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:e787b3ec90b2e065056171d138f57052f68c18e6ccde7106d819d6838ff94bb4
COMPONENT_PROJECT_URL=	http://www.nasm.us/
COMPONENT_ARCHIVE_URL=	http://www.nasm.us/pub/nasm/releasebuilds/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

IPS_COMPONENT_VERSION=	2.9.10

CFLAGS+="-I$(BUILD_DIR_$(BITS))"

COMPONENT_POST_CONFIGURE_ACTION += (mkdir -p $(BUILD_DIR_32)/lib $(BUILD_DIR_64)/lib)

COMPONENT_INSTALL_ENV += INSTALLROOT="$(PROTO_DIR)"

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

