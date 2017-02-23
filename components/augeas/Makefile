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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		augeas
COMPONENT_VERSION=	1.5.0
COMPONENT_PROJECT_URL=	http://www.augeas.net/
COMPONENT_ARCHIVE_HASH=	\
    sha256:223bb6e6fe3e9e92277dafd5d34e623733eb969a72a382998d204feab253f73f
COMPONENT_ARCHIVE_URL=	http://download.augeas.net/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	7017

TPNO=	29439

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
       ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS  +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=	--disable-dependency-tracking

COMPONENT_TEST_ARGS = -k
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

# XXX why does this coredump without the workaround?
# Fixes coredump in gnulib-test/test-localename test
CONFIGURE_OPTIONS  +=           ac_cv_func_newlocale=no

# Needed for "gmake test" to work.
# SHELLOPTS is exported via make-rules/shared-macros.mk,
# causing the braceexpand option to be set.
# This option causes "$1: unbound variable" errors during the check-TESTS,
# and the gnulib-tests don't even run at all.
# Note that the below unexports SHELLOPTS, even for targets
# other than "test." 
unexport SHELLOPTS

REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += system/library
