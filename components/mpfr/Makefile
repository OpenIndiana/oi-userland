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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
COMPILER=	gcc
include ../../make-rules/shared-macros.mk

PATH=$(dir $(CC)):$(USRBINDIR):$(GNUBIN)

COMPONENT_NAME=         mpfr
COMPONENT_VERSION=      3.1.5
COMPONENT_PROJECT_URL=	http://www.mpfr.org/
COMPONENT_ARCHIVE_HASH= \
    sha256:f4eb5070883aee3fd8b927751ea63ff95aebe24418cde852439ce74c3dd2513c
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libmpfr
COMPONENT_ANITYA_ID=	2019

TPNO=			33316
TPNO_2.4.2=		17709

COMPONENT_VERSION_1=      2.4.2
COMPONENT_SRC_1=          $(COMPONENT_NAME)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=      $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:246d7e184048b1fc48d3696dd302c9774e24e921204221540745e5464022b637
COMPONENT_ARCHIVE_URL_1=  $(COMPONENT_PROJECT_URL)$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE_1)


include $(WS_MAKE_RULES)/common.mk

# When gmp.h is installed in the default path, this can be removed.
CFLAGS +=	$(shell pkg-config --cflags libgmp)
LINT_FLAGS +=	$(shell pkg-config --cflags libgmp)

# Macros to configure, build, and install the old version so we can contiune
# to deliver runtime support for GCC until a newer build of GCC built against
# the new GNU MPFR is part of the CBE.  Once the newer GCC packages are 
# on the build systems, we can stop building and delivering the old version.
BUILD_OLD_DIR_32 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH32)
BUILD_OLD_DIR_64 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH64)

$(BUILD_OLD_DIR_32)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_64)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_32)/.configured:        BITS=32
$(BUILD_OLD_DIR_64)/.configured:        BITS=64
# GNU MP removed their workaround for pre-ANSI C compilers that didn't support
# 'const' in GMP 5.1 MPFR 2.4.2 still expects to find the workaround.
$(BUILD_OLD_DIR_32)/.configured:        CFLAGS += -D__gmp_const=const
$(BUILD_OLD_DIR_64)/.configured:        CFLAGS += -D__gmp_const=const

CONFIGURE_32 += $(BUILD_OLD_DIR_32)/.configured
CONFIGURE_64 += $(BUILD_OLD_DIR_64)/.configured

BUILD_32 += $(BUILD_OLD_DIR_32)/.built
BUILD_64 += $(BUILD_OLD_DIR_64)/.built

INSTALL_32 += $(BUILD_OLD_DIR_32)/.installed
INSTALL_64 += $(BUILD_OLD_DIR_64)/.installed

# install the old version first
$(BUILD_DIR_32)/.installed:     $(BUILD_OLD_DIR_32)/.installed
$(BUILD_DIR_64)/.installed:     $(BUILD_OLD_DIR_64)/.installed
#
# End old version

MPFRMULHIGH = 2048

CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-libtool-lock
CONFIGURE_OPTIONS += --enable-thread-safe
CONFIGURE_OPTIONS += --enable-tests-timeout=0
CONFIGURE_OPTIONS += --with-gmp-include=$(shell pkg-config --variable=includedir libgmp)
CONFIGURE_OPTIONS += --with-mulhigh-size=$(MPFRMULHIGH)
CONFIGURE_OPTIONS += --with-pic

COMPONENT_PREP_ACTION = (cd $(@D) ; $(AUTORECONF) -fiv)

# so lint can find the header
LINT_FLAGS += -I$(SOURCE_DIR)/src

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/^make\[[0-9]\{1,\}\]/make/g"' \
	'-e "s/.*MPFR tuning.*//g"' \
	'-n ' \
	'-e "/make:.*directory/p" ' \
	'-e "/Testsuite /p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/ERROR/p" ' \
	'-e "/=====/p" ' \
	'-e "/TOTAL/p" '

REQUIRED_PACKAGES += library/gmp
