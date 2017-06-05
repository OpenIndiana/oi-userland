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
# Copyright 2016 John Smith. All rights reserved.
#


include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sslh
COMPONENT_VERSION=	1.18
COMPONENT_PROJECT_URL=	http://www.rutschle.net/tech
COMPONENT_SRC=		$(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1601a5b377dcafc6b47d2fbb8d4d25cceb83053a4adcc5874d501a2d5a7745ad
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
# http://www.rutschle.net/tech/sslh/sslh-v1.18.tar.gz
COMPONENT_FMRI=		network/sslh
COMPONENT_SUMMARY=	Applicative protocol multiplexer
COMPONENT_CLASSIFICATION= System/Security


COMPONENT_LICENSE_FILE= COPYING
COMPONENT_LICENSE=	GPLv2

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin
LD_OPTIONS=-lresolv -lsocket -lnsl

include ../../../make-rules/prep.mk
include ../../../make-rules/justmake.mk
include ../../../make-rules/ips.mk

COMPONENT_BUILD_TARGETS += CC=gcc

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk


