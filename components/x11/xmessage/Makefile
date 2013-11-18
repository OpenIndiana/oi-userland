#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2011 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xmessage
COMPONENT_VERSION=	1.0.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:cfa35d3ad4ad1306e49878163982e9d54872a20a497e77ab0a8d5de05c8b3d5b
COMPONENT_ARCHIVE_URL=	http://xorg.freedesktop.org/archive/individual/app/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://xorg.freedesktop.org

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
