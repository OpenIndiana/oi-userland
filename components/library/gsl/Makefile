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
# Copyright (c) 2013-2016 Louis M. Picciano. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME			= gsl
COMPONENT_VERSION		= 2.1
COMPONENT_SUMMARY		= GSL - GNU Scientific Library
COMPONENT_SRC			= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE		= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH	= \
	sha256:59ad06837397617f698975c494fe7b2b698739a59e2fcf830b776428938a0c66
COMPONENT_ARCHIVE_URL	= ftp://ftp.gnu.org/gnu/gsl/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI			= library/math/gsl
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE		= GPL v3
COMPONENT_LICENSE_FILE	= $(COMPONENT_NAME).license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_BUILD_ENV +=	CFLAGS="$(CFLAGS)"

CONFIGURE_OPTIONS 	+=	--disable-static

include $(WS_TOP)/make-rules/shared-targets.mk

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
