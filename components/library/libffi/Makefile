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
# Copyright 2011-2013, EveryCity Ltd. All rights reserved.
# Copyright 2019, Michal Nowak
#

BUILD_BITS=		32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libffi
COMPONENT_VERSION=	3.3
COMPONENT_PROJECT_URL=	http://sourceware.org/libffi/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:72fba7922703ddfa7a028d513ac15a85c8d54c8d67f55fa5a4802885dc652056
COMPONENT_FMRI=		library/libffi
COMPONENT_SUMMARY=	Foreign Function Interface Library
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_ARCHIVE_URL=	https://github.com/libffi/libffi/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = (cd $(@D); $(AUTORECONF) -if)

CFLAGS += -DFFI_MMAP_EXEC_WRIT=1

CONFIGURE_OPTIONS  +=	--disable-static
CONFIGURE_OPTIONS  +=	--enable-shared
CONFIGURE_OPTIONS  +=	--disable-raw-api

COMPONENT_TEST_ENV=	CC="$(CC) $(CC_BITS)" CXX="$(CXX) $(CC_BITS)"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
