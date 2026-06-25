#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have been accompanied
# with this source.  A copy of the CDDL is also available via the
# Internet at http://www.illumos.org/license/CDDL.
#

#
# Copyright 2026 Akad Arpad Padak <akadarpadpadak@hotmail.com>
#

BUILD_BITS=		64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cmatrix
COMPONENT_VERSION=	2.0
COMPONENT_SUMMARY=	Terminal based Matrix screensaver
COMPONENT_PROJECT_URL=	https://github.com/abishekvashok/cmatrix
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/abishekvashok/cmatrix/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		sysutils/cmatrix
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

include ../../../make-rules/prep.mk
include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

CONFIGURE_OPTIONS += --with-ncurses
CFLAGS            += -I/usr/include/ncurses

COMPONENT_BUILD_ARGS =
COMPONENT_INSTALL_ARGS = DESTDIR=$(PROTODIR) install

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)
