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
# Copyright 2014-2017 Aurelien Larcher.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		check
COMPONENT_VERSION=	0.11.0
COMPONENT_FMRI=		developer/check
COMPONENT_SUMMARY=	Unit Testing Framework for C
COMPONENT_PROJECT_URL=	https://libcheck.github.io/check
COMPONENT_CLASSIFICATION=Development/C
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:24f7a48aae6b74755bcbe964ce8bc7240f6ced2141f8d9cf480bc3b3de0d5616
COMPONENT_ARCHIVE_URL=\
	https://github.com/libcheck/check/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS+=-std=gnu99

CONFIGURE_OPTIONS+=	--includedir=$(CONFIGURE_PREFIX)/include/check
CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+= --enable-gcov           
CONFIGURE_OPTIONS+= --enable-timeout-tests
# Needed to get all the tests to pass (problems with "inf/nan" vs "Inf/Nan").
CONFIGURE_OPTIONS+= --enable-snprintf-replacement

# Tests failure
unexport SHELLOPTS

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# All tests pass
test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/gawk
