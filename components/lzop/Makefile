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
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		lzop
COMPONENT_VERSION=	1.03
IPS_COMPONENT_VERSION=	1.0.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:c1425b8c77d49f5a679d5a126c90ea6ad99585a55e335a613cae59e909dbb2c9
COMPONENT_PROJECT_URL=	http://www.lzop.org
COMPONENT_ARCHIVE_URL=	http://www.lzop.org/download/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)
