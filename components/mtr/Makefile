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
# Copyright 2012, Jon Tibble
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		mtr
COMPONENT_VERSION=	0.82
COMPONENT_PROJECT_URL=	http://www.bitwizard.nl/mtr/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:f3b457c9623ae03565688a7ffd49d4843a5e2505ccaf3ba8d9fbd86e3ce9b6a0
COMPONENT_ARCHIVE_URL=	ftp://ftp.bitwizard.nl/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPILER=	gcc

CONFIGURE_OPTIONS+=	LIBS="-L/usr/gnu/lib -R/usr/gnu/lib -lncurses"

build:		$(BUILD_32)

install:	$(INSTALL_32)

