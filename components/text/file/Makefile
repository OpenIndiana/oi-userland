#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Jim Klimov
# Copyright 2016 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		file
COMPONENT_FMRI=		text/file
COMPONENT_VERSION=	5.25
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.darwinsys.com/file/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:3735381563f69fb4239470b8c51b876a80425348b8285a7cded8b61d6b890eca
COMPONENT_ARCHIVE_URL=	ftp://ftp.astron.com/pub/file/$(COMPONENT_ARCHIVE)
COMPONENT_SUMMARY=	utility for recognizing the type of data contained in a computer file using magic numbers
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	BSD

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk


