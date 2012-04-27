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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

PATH=$(SPRO_VROOT)/bin:$(JAVA_HOME)/bin:/usr/bin

COMPONENT_NAME=		db
COMPONENT_VERSION=	5.1.25
COMPONENT_PROJECT_URL=	http://www.oracle.com/technetwork/database/berkeleydb/overview/index.html
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:72eac5fcae4b51b0f1edc727c0368407f29b42e3f2f50ebc31a282d0d6c0a617
COMPONENT_ARCHIVE_URL=	http://download.oracle.com/berkeley-db/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk


COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))
COMPONENT_POST_TEST_ACTION = \
        (cd $(@D); \
        echo "source test/tcl/test.tcl" > $(@D)/run_bdb.tcl; \
        echo "$(RUN)" >> $(@D)/run_bdb.tcl; \
        cd $(@D); \
        ulimit -n 1024; $(ENV) /usr/bin/tclsh run_bdb.tcl)

CONFIGURE_SCRIPT = dist/configure

# adding to the C++ compiler because libtool appears to strip it from CXXFLAGS
CXX +=	$(studio_NORUNPATH)

# we need to enable large file support and build PIC for our shared libraries
CFLAGS += $(CPP_LARGEFILES) $(CC_PIC)
CXXFLAGS += $(CPP_LARGEFILES)

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"
CONFIGURE_ENV += JAVA_HOME="$(JAVA_HOME)"

CONFIGURE_OPTIONS += --includedir=/usr/include
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-cxx
CONFIGURE_OPTIONS += --enable-java
CONFIGURE_OPTIONS += --enable-sql
CONFIGURE_OPTIONS += --enable-sql_codegen
CONFIGURE_OPTIONS += --enable-jdbc
CONFIGURE_OPTIONS += --enable-tcl
CONFIGURE_OPTIONS += --with-tcl=/usr/lib
CONFIGURE_OPTIONS += --enable-dbm
CONFIGURE_OPTIONS += $(configure_test)

COMPONENT_TEST_TARGETS = test

$(BUILD_DIR)/%/.tested: configure_test= --enable-test

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)
		$(CP) berkeleydb.license $(PROTOUSRDIR)/docs/LICENSE

test:		$(TEST_32_and_64) 

# By default "gmake test" runs standard tests, takes ~6 hrs (default).
RUN=run_std

# Run all tests, takes ~3 days from command line using 
# "gmake test RUN=run_all"

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
