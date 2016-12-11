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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
export PARFAIT_BUILD=no
include ../../make-rules/shared-macros.mk

COMPONENT_NAME        = mysql
COMPONENT_VERSION     = 5.6.33
COMPONENT_SRC         = $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE     = $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
         sha256:60776ec27d78b59f597e71738c5bcdea64dcba33c36fede320d5930320b1fef0
COMPONENT_ARCHIVE_URL = http://cdn.mysql.com/Downloads/MySQL-5.6/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://dev.mysql.com/ 
COMPONENT_BUGDB       = database/mysql

# Requires newer version of system/library/c++-runtime from Studio, available
# in S12 but not 11.3, so do not publish.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

#We use cp(1) instead of cloney because we use TAR to copy files and the TAR 
#used doesn't handle long links
CLONEY = echo
COMPONENT_PRE_BUILD_ACTION +=  $(CP) -rp $(SOURCE_DIR)/* $(@D);

BUILD_STYLE= cmake
TEST_TARGET= $(NO_TESTS)
SYSTEM_TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# MySQL being one of Oracle's own product doesn't require to have a
# TPNO License number.

# This component uses cmake to generate Makefiles and thus does not
# run any configure script
CMAKE               = $(shell which cmake)
CMAKE_PREFIX        = $(USRDIR)/mysql/5.6
CONFDIR             = $(ETCDIR)/mysql/5.6
DATA_PREFIX         = $(VARDIR)/mysql/5.6

CMAKE_BINDIR.32     = bin/$(MACH32)
CMAKE_BINDIR.64     = bin
CMAKE_LIBDIR.32     = lib
CMAKE_LIBDIR.64     = lib/$(MACH64)
CMAKE_PLUGINDIR.32  = lib/plugin
CMAKE_PLUGINDIR.64  = lib/$(MACH64)/plugin
CMAKE_CFLAGS.32     = -m32
CMAKE_CFLAGS.64     = -m64
CMAKE_CXXFLAGS.32   = -m32 -norunpath -std=c++03
CMAKE_CXXFLAGS.64   = -m64 -norunpath -std=c++03

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
CMAKE_OPTIONS += -DWITH_SSL=bundled
CMAKE_OPTIONS += -DWITH_READLINE=ON
CMAKE_OPTIONS += -DENABLE_DTRACE=1
CMAKE_OPTIONS += -DHAVE_REAL_DTRACE_INSTRUMENTING=ON
CMAKE_OPTIONS += -DWITH_EXTRA_CHARSETS=complex
CMAKE_OPTIONS += -DENABLED_LOCAL_INFILE=ON
CMAKE_OPTIONS += -DWITH_ARCHIVE_STORAGE_ENGINE=1
CMAKE_OPTIONS += -DWITH_BLACKHOLE_STORAGE_ENGINE=1
CMAKE_OPTIONS += -DWITH_EXAMPLE_STORAGE_ENGINE=1
CMAKE_OPTIONS += -DWITH_FEDERATED_STORAGE_ENGINE=1
CMAKE_OPTIONS += -DCMAKE_CXX_COMPILER=$(CXX)
CMAKE_OPTIONS += -DCMAKE_C_COMPILER=$(CC)
CMAKE_OPTIONS += -DWITH_INNOBASE_STORAGE_ENGINE=1
CMAKE_OPTIONS += -DCMAKE_C_FLAGS="$(CMAKE_CFLAGS.$(BITS))"
CMAKE_OPTIONS += -DCMAKE_CXX_FLAGS="$(CMAKE_CXXFLAGS.$(BITS))"
CMAKE_OPTIONS += '-DCOMPILATION_COMMENT=MySQL Community Server (GPL)'
CMAKE_OPTIONS += -DFEATURE_SET=community
CMAKE_OPTIONS += -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE

# Adjust '#!/usr/bin/perl'
$(INSTALL_64): PERL_SCRIPTS= \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysql_convert_table_format \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysql_find_rows \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysql_fix_extensions \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysql_install_db \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysql_secure_installation \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysql_setpermission \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysql_zap \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysqlaccess \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysqld_multi \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysqldumpslow \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysqlhotcopy

REQUIRED_PACKAGES += database/mysql-56/client
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/network
