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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

COMPILER = gcc

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		augeas
COMPONENT_VERSION=	1.3.0
COMPONENT_PROJECT_URL=	http://www.augeas.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:80763031af76515a8ea66013ddc3c466742a15d2e907c7c8e2e3b7410262e2af
COMPONENT_ARCHIVE_URL=	http://download.augeas.net/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/augeas

TPNO=	21660

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_BINDIR.64 =	$(CONFIGURE_PREFIX)/bin

COMPONENT_PRE_CONFIGURE_ACTION = \
       ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_PREFIX    =	/usr
CONFIGURE_OPTIONS  +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=	--disable-dependency-tracking
CONFIGURE_OPTIONS  +=	CFLAGS="$(CFLAGS)"

COMPONENT_TEST_ARGS = -k

# Fixes coredump in gnulib-test/test-localename test
CONFIGURE_OPTIONS  +=           ac_cv_func_newlocale=no

ASLR_MODE = $(ASLR_ENABLE)

# Needed for "gmake test" to work.
# SHELLOPTS is exported via make-rules/shared-macros.mk,
# causing the braceexpand option to be set.
# This option causes "$1: unbound variable" errors during the check-TESTS,
# and the gnulib-tests don't even run at all.
# Note that the below unexports SHELLOPTS, even for targets
# other than "test." 
unexport SHELLOPTS

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/ncurses
