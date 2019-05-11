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
# Copyright 2016 Alexander Pyhalov
# Copyright 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		lz4
COMPONENT_VERSION=	1.9.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_SUMMARY=	Extremely Fast Compression algorithm
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:f8377c89dad5c9f266edc0be9b73595296ecafd5bfa1000de148096c50052dc4
COMPONENT_ARCHIVE_URL= \
	https://github.com/lz4/lz4/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=	https://lz4.github.io/lz4/
COMPONENT_FMRI=		library/lz4
COMPONENT_LICENSE=	BSD,GPLv2
COMPONENT_LICENSE_FILE=	lz4.license
COMPONENT_CLASSIFICATION= System/Libraries

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

BINDIR.32=/usr/bin
BINDIR.64=/usr/bin/$(MACH64)
LIBDIR.32=/usr/lib
LIBDIR.64=/usr/lib/$(MACH64)

COMMON_ENV = CC=$(CC)
COMMON_ENV += CFLAGS="$(CFLAGS)"
COMMON_ENV += PREFIX=/usr
COMMON_ENV += BINDIR=$(BINDIR.$(BITS))
COMMON_ENV += LIBDIR=$(LIBDIR.$(BITS))

COMPONENT_BUILD_ENV = $(COMMON_ENV)
COMPONENT_INSTALL_ENV = $(COMMON_ENV)
COMPONENT_TEST_ENV = $(COMMON_ENV)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
