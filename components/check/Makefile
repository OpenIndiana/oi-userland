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
# Copyright 2014 Aurelien Larcher.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		check
COMPONENT_VERSION=	0.10.0
COMPONENT_FMRI=		developer/check
COMPONENT_CLASSIFICATION=Development/C
COMPONENT_PROJECT_URL=	http://check.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f5f50766aa6f8fe5a2df752666ca01a950add45079aa06416b83765b1cf71052
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/check/files/check/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_BUGDB=	$(COMPONENT_FMRI)
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

COMPONENT_SUMMARY=	Unit Testing Framework for C

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_INCLUDEDIR =	$(CONFIGURE_INCLUDEROOTDIR)/$(COMPONENT_NAME)

CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+= --enable-gcov
CONFIGURE_OPTIONS+= --enable-timeout-tests

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

#
# All tests pass for the checkmk program.
# Some tests are known to fail in check-TESTS both in 32 and 64 bits:
# Running suite(s): Fix Sub
# 	0%: Checks: 1, Failures: 1, Errors: 0
# Running suite(s): Check Servant 2
#	27%: Checks: 146, Failures: 58, Errors: 48
# Running suite(s): Setup Fail
#	0%: Checks: 1, Failures: 1, Errors: 0
# Running suite(s): Setup Fail Nofork
#	0%: Checks: 1, Failures: 1, Errors: 0
# Running suite(s): Setup Fail Nofork 2
#	0%: Checks: 1, Failures: 1, Errors: 0
# Running suite(s): Setup Sig
#	0%: Checks: 1, Failures: 0, Errors: 1
# Running suite(s): Teardown Fail
#	0%: Checks: 1, Failures: 1, Errors: 0
# Running suite(s): Teardown Fail No Fork
#	0%: Checks: 1, Failures: 1, Errors: 0
# Running suite(s): Teardown Sig
#	0%: Checks: 1, Failures: 0, Errors: 1
#
# Exits with 7 passed test suites.
#

test:		$(TEST_32_and_64)

