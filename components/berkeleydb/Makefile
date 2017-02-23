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
include ../../make-rules/shared-macros.mk

# Separate build for test with --enable-test configured
CONFIGURE_32_and_64 += $(BUILD_DIR)/test-$(MACH32)/.configured
CONFIGURE_32_and_64 += $(BUILD_DIR)/test-$(MACH64)/.configured
BUILD_32_and_64 += $(BUILD_DIR)/test-$(MACH32)/.built
BUILD_32_and_64 += $(BUILD_DIR)/test-$(MACH64)/.built
$(BUILD_DIR)/test-$(MACH32)/.built:	BITS=32
$(BUILD_DIR)/test-$(MACH64)/.built:	BITS=64
INSTALL_32_and_64 += $(BUILD_DIR)/test-$(MACH32)/.installed
INSTALL_32_and_64 += $(BUILD_DIR)/test-$(MACH64)/.installed
$(BUILD_DIR)/test-$(MACH32)/.installed:    BITS=32
$(BUILD_DIR)/test-$(MACH64)/.installed:    BITS=64
TEST_TARGET= $(BUILD_DIR)/test-$(MACH32)/.tested $(BUILD_DIR)/test-$(MACH64)/.tested

PATH=$(SPRO_VROOT)/bin:/usr/bin

COMPONENT_NAME=		berkeleydb
COMPONENT_VERSION=	5.3.21
COMPONENT_PROJECT_URL=	http://www.oracle.com/technetwork/database/berkeleydb/overview/index.html
COMPONENT_SRC_NAME=	db
COMPONENT_ARCHIVE_HASH=	\
    sha256:ddd92a930317df92021054c03992392db9ea5cddba43bef8920d392a82114fb8
COMPONENT_ARCHIVE_URL=	http://download.oracle.com/berkeley-db/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	database/berkeley
COMPONENT_ANITYA_ID=	1587

# Userland default optimization level is 4, but that causes test failures.
# Upstream recommends level 2, which allows the tests to run, so we use that.
studio_OPT = -xO2

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

# Berkeley DB uses TCLSH to run all the test suite test cases.
# Per the test suite instructions in the BDB build manual, the tclsh
# include path must be correct in include.tcl then tclsh is run by
# sourcing the test.tcl header and finally running the "run_std" command.
# COMPONENT_POST_TEST_ACTION does this.

COMPONENT_POST_TEST_ACTION = \
        (cd $(@D); \
        echo "source test/tcl/test.tcl" > $(@D)/run_bdb.tcl; \
        echo "$(RUN)" >> $(@D)/run_bdb.tcl; \
        cd $(@D); \
	$(CP) include.tcl include.tcl.orig; \
	$(GSED) \
	    's;set tclsh_path .*;set tclsh_path '$(TCLSH)';' \
	    < include.tcl.orig > include.tcl; \
	ulimit -n 65535; \
        $(ENV) $(TCLSH) run_bdb.tcl)

CONFIGURE_SCRIPT = dist/configure

# adding to the C++ compiler because libtool appears to strip it from CXXFLAGS
CXX +=	$($(COMPILER)_NORUNPATH)

# we need to enable large file support and build PIC for our shared libraries
CFLAGS += $(CPP_LARGEFILES) $(CC_PIC)
CXXFLAGS += $(CPP_LARGEFILES)

# BerkeleyDB < 6 does not support Java 8. Java 7 is EOL & removed.
CONFIGURE_OPTIONS += --disable-java
CONFIGURE_OPTIONS += --disable-jdbc
CONFIGURE_OPTIONS += --includedir=$(USRINCDIR)
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-cxx
CONFIGURE_OPTIONS += --enable-sql
CONFIGURE_OPTIONS += --enable-sql_codegen
CONFIGURE_OPTIONS += --enable-tcl
CONFIGURE_OPTIONS += --with-tcl=$(USRLIBDIR)
CONFIGURE_OPTIONS += --enable-dbm
CONFIGURE_OPTIONS += $(configure_test)

COMPONENT_TEST_TARGETS = test

$(SKIP_TEST_AT_TOP_LEVEL)

$(BUILD_DIR)/test-%/.configured: configure_test= --enable-test

# Do not apply the standard licence transforms for this component.
LICENSE_TRANSFORMS =

COMPONENT_POST_INSTALL_ACTION += \
	$(CP) berkeleydb.license $(PROTOUSRDIR)/docs/LICENSE

# By default "gmake test" runs standard tests, takes ~2 days per $(BITS).
RUN=run_std


REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/c++-runtime
