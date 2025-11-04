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
# Copyright 2012-2013, EveryCity Ltd. All rights reserved.
# Copyright 2016, Jim Klimov
#

BUILD_BITS = NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zetaback
COMPONENT_VERSION=	1.0.7
COMPONENT_REVISION =	2
COMPONENT_PROJECT_URL=	https://github.com/omniti-labs/$(COMPONENT_NAME)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:b10c6df2b27d823f5fc18e4c7c8460e8231a86d32d89f9c73a916a7b15f98888
COMPONENT_ARCHIVE_URL=	https://github.com/omniti-labs/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION= $(CLONEY) $(SOURCE_DIR) $(@D)
COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -vif )

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
