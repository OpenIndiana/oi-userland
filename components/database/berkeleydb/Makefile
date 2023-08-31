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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2018, Michal Nowak
#
BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		berkeleydb
COMPONENT_VERSION=	5.3.28
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	Berkeley DB is a computer software library that provides a high-performance embedded database for key/value data
COMPONENT_PROJECT_URL=	https://www.oracle.com/technetwork/database/database-technologies/berkeleydb/overview/index.html
COMPONENT_SRC_NAME=	db
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:e0a992d740709892e81f9d93f06daf305cf73fb81b545afe72478043172c3628
COMPONENT_ARCHIVE_URL=	https://download.oracle.com/berkeley-db/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	database/berkeleydb-5
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_LICENSE=	berkeleydb license

include $(WS_MAKE_RULES)/common.mk

PATH=/usr/gnu/bin:$(JAVA_HOME)/bin:/usr/bin

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

# Berkeley DB uses TCLSH to run all the test suite test cases.
# Per the test suite instructions in the BDB build manual, the tclsh
# include path must be correct in include.tcl then tclsh is run by
# sourcing the test.tcl header and finally running the "run_std" command.
# COMPONENT_POST_TEST_ACTION does this after BDB has been recompiled
# for test (--enable-test)

COMPONENT_POST_TEST_ACTION = \
        (cd $(@D); \
        echo "source test/tcl/test.tcl" > $(@D)/run_bdb.tcl; \
        echo "$(RUN)" >> $(@D)/run_bdb.tcl; \
        cd $(@D); \
	$(CP) include.tcl include.tcl.orig; \
	$(GSED) \
	    's;set tclsh_path .*;set tclsh_path '$(TCLSH)';' \
	    < include.tcl.orig > include.tcl; \
        $(ENV) $(TCLSH) run_bdb.tcl)

CONFIGURE_SCRIPT = dist/configure

# adding to the C++ compiler because libtool appears to strip it from CXXFLAGS
# CXX +=	$(studio_NORUNPATH)

# we need to enable large file support and build PIC for our shared libraries
CFLAGS += $(CPP_LARGEFILES) $(CC_PIC)
CXXFLAGS += $(CPP_LARGEFILES)

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += HOSTCC="$(CC)"
CONFIGURE_ENV += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"
CONFIGURE_ENV += JAVA_HOME="$(JAVA_HOME)"

CONFIGURE_OPTIONS += --includedir=/usr/include
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-cxx
CONFIGURE_OPTIONS += --disable-java
CONFIGURE_OPTIONS += --enable-sql
CONFIGURE_OPTIONS += --enable-sql_codegen
CONFIGURE_OPTIONS += --disable-jdbc
CONFIGURE_OPTIONS += --enable-tcl
CONFIGURE_OPTIONS += --with-tcl=/usr/lib
CONFIGURE_OPTIONS += --enable-dbm
CONFIGURE_OPTIONS += $(configure_test)

# Don't use rpath
COMPONENT_POST_CONFIGURE_ACTION.32 = \
	(cd $(BUILD_DIR_32) ; \
	find . -name libtool -exec $(GSED) -i 's|^hardcode_libdir_flag_spec=.*|hardcode_libdir_flag_spec=""|g' {} \; ; \
	find . -name libtool -exec $(GSED) -i 's|^runpath_var=LD_RUN_PATH|runpath_var=DIE_RPATH_DIE|g' {} \;)
COMPONENT_POST_CONFIGURE_ACTION.64 = \
	(cd $(BUILD_DIR_64) ; \
	find . -name libtool -exec $(GSED) -i 's|^hardcode_libdir_flag_spec=.*|hardcode_libdir_flag_spec=""|g' {} \; ; \
	find . -name libtool -exec $(GSED) -i 's|^runpath_var=LD_RUN_PATH|runpath_var=DIE_RPATH_DIE|g' {} \;)
COMPONENT_POST_CONFIGURE_ACTION = $(COMPONENT_POST_CONFIGURE_ACTION.$(BITS))

COMPONENT_TEST_TARGETS = test

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

$(BUILD_DIR)/%/.tested: configure_test= --enable-test

# Do not apply the standard licence transforms for this component.
LICENSE_TRANSFORMS =

install:	$(INSTALL_32_and_64)
		$(CP) berkeleydb.license $(PROTOUSRDIR)/docs/LICENSE

# By default "gmake test" runs standard tests, takes ~2 days per $(BITS).
RUN=run_std

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
