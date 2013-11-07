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
# Copyright (c) 2013 Louis M. Picciano. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME			= gsl
COMPONENT_VERSION		= 1.16
COMPONENT_SUMMARY	= GSL - GNU Scientific Library
COMPONENT_SRC			= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE		= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH	= \
	sha256:73bc2f51b90d2a780e6d266d43e487b3dbd78945dd0b04b14ca5980fe28d2f53
COMPONENT_ARCHIVE_URL=	http://gnu.mirrorcatalogs.com/gsl/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_BUILD_ENV +=	CFLAGS="$(CFLAGS)"

include ../../make-rules/shared-targets.mk
	
build:		$(BUILD_32_and_64)
#$(BUILD_64)

install:	$(INSTALL_32_and_64)
#$(INSTALL_64)

test:		$(TEST_32_and_64)
#$(TEST_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
