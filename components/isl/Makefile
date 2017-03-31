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
COMPILER=	gcc
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         isl
COMPONENT_VERSION=      0.18
COMPONENT_PROJECT_URL=  http://freecode.com/projects/isl
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:6b8b0fd7f81d0a957beb3679c81bbb34ccc7568d5682844d8924424a0dadcb1b
COMPONENT_ARCHIVE_URL=  http://isl.gforge.inria.fr/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=        utility/gnu-compiler
COMPONENT_ANITYA_ID=	13286

TPNO=			33315

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = (cd $(@D) ; $(AUTORECONF) -fiv)

# When gmp.h is installed in the default path, this can be removed.
CFLAGS +=	$(shell pkg-config --cflags libgmp)

CONFIGURE_OPTIONS  +=		--localstatedir=$(VARDIR)
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--enable-shared=yes
CONFIGURE_OPTIONS  +=		--enable-static=no
CONFIGURE_OPTIONS  +=		--disable-libtool-lock
CONFIGURE_OPTIONS  +=		--with-pic
CONFIGURE_OPTIONS  +=		--with-gmp=system
CONFIGURE_OPTIONS  +=		--with-clang=no

COMPONENT_TEST_ENV +=	-i

COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-isl.master

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/^make\[[0-9]\{1,\}\]/make/g"' \
	'-n ' \
	'-e "/make:.*directory/p" ' \
	'-e "/Testsuite /p" ' \
	'-e "/tversion\]/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/ERROR/p" ' \
	'-e "/=====/p" ' \
	'-e "/TOTAL/p" '

REQUIRED_PACKAGES += library/gmp
