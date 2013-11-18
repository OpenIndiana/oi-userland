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

COMPONENT_NAME=		json-c
COMPONENT_VERSION=	0.10
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:274fc9d47c1911fad9caab4db117e4be5d6b68c4547eab0c508d79c4768e170c
COMPONENT_PROJECT_URL=	https://github.com/json-c/json-c
COMPONENT_ARCHIVE_URL=	http://github.com/downloads/json-c/json-c/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS += --disable-static

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D))

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)
