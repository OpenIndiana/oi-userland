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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#

# MySQL 5.7 is compiled using GCC. Note that the MySQL Server 5.7 for
# Solaris dowloaded from http://dev.mysql.com/downloads/mysql/ is a
# hybrid, the server part is compiled using GCC and the client library
# is compiled using SunStudio and the "stlport4" C++ runtime
# library. In this build both server and client is compiled using GCC.
COMPILER              = gcc

BUILD_BITS= 64
export PARFAIT_BUILD=no
include ../../make-rules/shared-macros.mk

COMPONENT_NAME        = mysql
COMPONENT_VERSION     = 5.7.17
COMPONENT_SRC         = $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE     = $(COMPONENT_NAME)-boost-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
         sha256:b75bba87199ef6a6ccc5dfbcaf70949009dc12089eafad8c5254afc9002aa903
COMPONENT_ARCHIVE_URL = http://cdn.mysql.com/Downloads/MySQL-5.7/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://dev.mysql.com/ 
COMPONENT_BUGDB       = database/mysql

# Requires new pkgmogrify feature, available in S12 but not 11.3, so do not
# publish.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

#We use cp(1) instead of cloney because we use TAR to copy files and the TAR 
#used doesn't handle long links
CLONEY=echo
COMPONENT_PRE_BUILD_ACTION = $(CP) -r $(SOURCE_DIR)/* $(@D);

BUILD_STYLE= cmake
TEST_TARGET= $(NO_TESTS)
SYSTEM_TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# MySQL being one of Oracle's own product doesn't require to have a TPNO
# License number, but it uses Boost, which does have such a requirement.
TPNO=24164

# This component uses cmake to generate Makefiles and thus does not
# run any configure script
CMAKE               = $(shell which cmake)
CMAKE_PREFIX        = $(USRDIR)/mysql/5.7
CONFDIR             = $(ETCDIR)/mysql/5.7
DATA_PREFIX         = $(VARDIR)/mysql/5.7

# The install layout differs from "INSTALL_LAYOUT=STANDALONE" in that
# we put scripts into the "bin" directory and the "lib" directory has
# an architecture subdirectory. We also use a simplified CFLAGS/CXXFLAGS
# setting and let the MySQL CMake setup add the other flags.
# For "lib", 64-bit uses subdir but 32-bit does not
CMAKE_BINDIR.64     = bin
CMAKE_LIBDIR.64     = lib/$(MACH64)
CMAKE_PLUGINDIR.64  = lib/$(MACH64)/plugin

# Providing component specific build options to cmake
CMAKE_OPTIONS += -DBUILD_CONFIG=mysql_release
CMAKE_OPTIONS += -DINSTALL_LAYOUT=STANDALONE
CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX=$(CMAKE_PREFIX)
CMAKE_OPTIONS += -DINSTALL_BINDIR=$(CMAKE_BINDIR.$(BITS))
CMAKE_OPTIONS += -DINSTALL_SBINDIR=$(CMAKE_BINDIR.$(BITS))
CMAKE_OPTIONS += -DINSTALL_SCRIPTDIR=$(CMAKE_BINDIR.$(BITS))
CMAKE_OPTIONS += -DINSTALL_LIBDIR=$(CMAKE_LIBDIR.$(BITS))
CMAKE_OPTIONS += -DINSTALL_PLUGINDIR=$(CMAKE_PLUGINDIR.$(BITS))
CMAKE_OPTIONS += -DSYSCONFDIR=$(CONFDIR)
CMAKE_OPTIONS += -DMYSQL_DATADIR=$(DATA_PREFIX)
CMAKE_OPTIONS += -DENABLED_LOCAL_INFILE=ON
CMAKE_OPTIONS += -DCMAKE_CXX_COMPILER=$(CXX)
CMAKE_OPTIONS += -DCMAKE_C_COMPILER=$(CC)

CMAKE_OPTIONS += '-DCOMPILATION_COMMENT=MySQL Community Server (GPL)'
CMAKE_OPTIONS += -DFEATURE_SET=community

CMAKE_OPTIONS += -DWITH_SSL=bundled
CMAKE_OPTIONS += -DENABLE_DTRACE=1
CMAKE_OPTIONS += -DWITH_INNODB_MEMCACHED=1
CMAKE_OPTIONS += -DWITH_BOOST=boost
CMAKE_OPTIONS += -DWITH_EMBEDDED_SERVER=1
CMAKE_OPTIONS += -DWITH_EMBEDDED_SHARED_LIBRARY=1
CMAKE_OPTIONS += -DDISABLE_STATIC=ON
CMAKE_OPTIONS += -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE

verify-p5m:	
	$(MAKE) $(MAKEFLAGS) sample-manifest METADATA_TEMPLATE=
        # For easier parsing, remove backslash+newline
	perl -pe 's,\\\n,,' $(BUILD_DIR)/manifest-$(MACH)-generated.p5m \
	> $(BUILD_DIR)/manifest-generated.p5m
  	# Generate a new version of "mysql-57test.p5m.include"
	cat $(BUILD_DIR)/manifest-generated.p5m | \
	egrep -v mangled | egrep '/(mysql-test|sql-bench)(/|$$)' \
	>  $(BUILD_DIR)/mysql-57test.p5m.include
	-diff -U0 mysql-57test.p5m.include $(BUILD_DIR)/mysql-57test.p5m.include > \
	$(BUILD_DIR)/mysql-57test.p5m.include.diff
	@if [ -s $(BUILD_DIR)/mysql-57test.p5m.include.diff ] ; then \
        echo "ERROR: \"mysql-57test.p5m.include\" need to be updated, you can find the new suggested content in" ; \
        echo "       \"$(BUILD_DIR)/mysql-57test.p5m.include\", see" ; \
        echo "       \"$(BUILD_DIR)/mysql-57test.p5m.include.diff\"" ; \
      	exit 1 ; \
	fi
       	# Find all file names outside "mysql-test" and "sql-bench"
       	# If you for some reason deliberately want to leave out some
       	# file from the IPS package but yet install if building from
       	# source, you add a "egrep -v ...." below
	cat $(BUILD_DIR)/manifest-generated.p5m | \
        egrep -v mangled | egrep -v '/(mysql-test|sql-bench)(/|$$)' | \
        perl -ne 'm,^(file|link)\s+path=([^ \n]+), and print $$2, "\n"' | sort \
      	 > $(BUILD_DIR)/all-installed
	perl -pe 's,\\\n,,' *.p5m | \
        perl -ne 'm,^(file|link)\s+path=([^ \n]+), and print $$2, "\n"' | sort \
         > $(BUILD_DIR)/all-specified
	comm -2 -3 build/all-installed build/all-specified > build/missing-specifications
	@if [ -s $(BUILD_DIR)/missing-specifications ] ; then \
	echo "ERROR: A file installed is not packaged, i.e. not mentioned in any \"*.p5m\" file, see" ; \
	echo "       \"$(BUILD_DIR)/missing-specifications\"" ; \
	exit 1 ; \
	fi
	@echo "No problems found!"

REQUIRED_PACKAGES += database/mysql-57/client
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/network
