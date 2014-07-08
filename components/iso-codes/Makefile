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
# Copyright 2013 Adam Stevko. All rights reserved.
# Copyright 2014 Ken Mays. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		iso-codes
COMPONENT_VERSION=	3.55
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:6c48f417160fa5f9e6874c19a07b220654974594a838460fdba06965c77e94e6
COMPONENT_PROJECT_URL=	http://alioth.debian.org/projects/pkg-isocodes
#COMPONENT_ARCHIVE_URL=	http://pkg-isocodes.alioth.debian.org/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_URL=	http://ftp.lfs-matrix.net/pub/blfs/conglomeration/iso-codes/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)
