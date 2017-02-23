#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		check
COMPONENT_VERSION=	0.10.0
COMPONENT_PROJECT_URL=	https://libcheck.github.io/check
COMPONENT_ARCHIVE_HASH=	\
    sha256:f5f50766aa6f8fe5a2df752666ca01a950add45079aa06416b83765b1cf71052
COMPONENT_ARCHIVE_URL=	https://github.com/libcheck/$(COMPONENT_NAME)/files/71408/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	7593

TPNO=			28147

SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_32_and_64)
include $(WS_MAKE_RULES)/common.mk

# Several tests fail when the Studio compiler is used.
COMPILER =      gcc

# Override tests in m4/acx_pthread.m4 that try to set obsolete/incompatible
# flags for linking threaded code on Solaris.
PTHREAD_CFLAGS = -D__EXTENSIONS__
ifeq ($(BUILD_TYPE), evaluation)
# No longer needed on S12 due to PSARC/2014/019, but still needed on S11
PTHREAD_CFLAGS += -D_POSIX_PTHREAD_SEMANTICS
endif
CONFIGURE_OPTIONS += PTHREAD_CFLAGS="$(PTHREAD_CFLAGS)"
CONFIGURE_OPTIONS += PTHREAD_LIBS="-lc"

# Master test results are the same for 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
	'-e "/passed/p" ' \
	'-e "/failed/p" ' \
	'-e "/Checks:/p" ' \
	'-e "/Total:/p" ' \
	'-e "/Passed/p" ' \
	'-e "/Failed/p" ' \
	'-e "/Failure expected/p" ' \
        '-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
        '-e "/FAIL/p" '

COMPONENT_SYSTEM_TEST_ENV =	CHECKMK_SCRIPT=$(USRBINDIR)/checkmk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

REQUIRED_PACKAGES +=	system/library/math
REQUIRED_PACKAGES +=	text/gawk
