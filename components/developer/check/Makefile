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
# Copyright 2020, Michal Nowak
#

BUILD_BITS=		32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		check
COMPONENT_VERSION=	0.13.0
COMPONENT_FMRI=		developer/check
COMPONENT_SUMMARY=	Unit Testing Framework for C
COMPONENT_PROJECT_URL=	https://libcheck.github.io/check
COMPONENT_CLASSIFICATION=Development/C
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:c4336b31447acc7e3266854f73ec188cdb15554d0edd44739631da174a569909
COMPONENT_ARCHIVE_URL=\
	https://github.com/libcheck/check/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPLv2

include $(WS_MAKE_RULES)/common.mk

CFLAGS+=-std=gnu99

CONFIGURE_OPTIONS+= --includedir=$(CONFIGURE_PREFIX)/include/check
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --disable-gcov           
CONFIGURE_OPTIONS+= --enable-timeout-tests
# Needed to get all the tests to pass (problems with "inf/nan" vs "Inf/Nan").
CONFIGURE_OPTIONS+= --enable-snprintf-replacement

# Tests failure
unexport SHELLOPTS

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/gawk
