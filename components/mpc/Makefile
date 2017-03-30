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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		mpc
COMPONENT_VERSION=	1.0.3
COMPONENT_PROJECT_URL=	http://www.multiprecision.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:617decc6ea09889fb08ede330917a00b16809b8db88c29c31bfbb49cbf88ecc3
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)mpc/download/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	1667

TPNO=			29500

#
# Temporarily build the old version to transition GCC 4.9 & 5.  Once GCC has
# been built against the new version, the old version can be removed.
#
# Begin old version
#
COMPONENT_VERSION_1=	0.9
COMPONENT_SRC_1=	$(COMPONENT_NAME)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:fd3efe422f0d454592059e80f2c00d1a2e381bf2beda424c5094abd4deb049ac
COMPONENT_ARCHIVE_URL_1=  $(COMPONENT_PROJECT_URL)$(COMPONENT_SRC_1)/$(COMPONENT_ARCHIVE_1)
COMPONENT_ANITYA_ID_1=	1667

TPNO_1=			4706

# Macros to configure, build, and install the old version for the time being.
BUILD_OLD_DIR_32 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH32)
BUILD_OLD_DIR_64 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH64)

$(BUILD_OLD_DIR_32)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_64)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_32)/.configured: BITS=32
$(BUILD_OLD_DIR_64)/.configured: BITS=64

BUILD_32 += $(BUILD_OLD_DIR_32)/.built
BUILD_64 += $(BUILD_OLD_DIR_64)/.built

INSTALL_32 += $(BUILD_OLD_DIR_32)/.installed
INSTALL_64 += $(BUILD_OLD_DIR_64)/.installed

# install the old version first
$(BUILD_DIR_32)/.installed:     $(BUILD_OLD_DIR_32)/.installed
$(BUILD_DIR_64)/.installed:     $(BUILD_OLD_DIR_64)/.installed
#
# End old version

TEST_TARGET= install $(TEST_32_and_64)
# Add install dependency when system-test target is implemented.
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS  +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=	--with-gmp-include=$(shell pkg-config --variable=includedir libgmp)
CONFIGURE_OPTIONS  +=	--with-mpfr-include=$(shell pkg-config --variable=includedir libmpfr)
CONFIGURE_OPTIONS  +=	--disable-static

COMPONENT_TEST_DIR =	$(BUILD_DIR)/$(MACH$(BITS))/tests
COMPONENT_TEST_MASTER =	$(COMPONENT_TEST_RESULTS_DIR)/results-all.master

PKG_MACROS +=		COMPONENT_VERSION_1=$(COMPONENT_VERSION_1)

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/=====/p" ' \
	'-e "/^Testsuite/p" ' \
	'-e "/TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" '

REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/mpfr
REQUIRED_PACKAGES += system/library/math
