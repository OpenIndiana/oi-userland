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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
export PARFAIT_BUILD=no
include ../../make-rules/shared-macros.mk

COMPONENT_NAME        = mysql
COMPONENT_VERSION     = 5.5.54
COMPONENT_ARCHIVE_HASH= \
    sha256:273bcbcf8cc84061eb07c359308563b2029eb3f70f78b558905bc1b5c5791ab8
COMPONENT_ARCHIVE_URL = http://cdn.mysql.com/Downloads/MySQL-5.5/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://dev.mysql.com/ 
COMPONENT_BUGDB       = database/mysql
COMPONENT_ANITYA_ID=	334

#We use cp(1) instead of cloney because we use TAR to copy files and the TAR 
#used doesn't handle long links
CLONEY = echo
COMPONENT_PRE_BUILD_ACTION += $(CP) -rp $(SOURCE_DIR)/* $(@D);

BUILD_STYLE= cmake
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# This component uses cmake to generate Makefiles and thus does not
# run any configure script
CMAKE_PREFIX        = $(USRDIR)/mysql/5.5
CONFDIR             = $(ETCDIR)/mysql/5.5
DATA_PREFIX         = $(VARDIR)/mysql/5.5

CMAKE_BINDIR.32     = bin/$(MACH32)
CMAKE_BINDIR.64     = bin
CMAKE_LIBDIR.32     = lib
CMAKE_LIBDIR.64     = lib/$(MACH64)
CMAKE_PLUGINDIR.32  = lib/plugin
CMAKE_PLUGINDIR.64  = lib/$(MACH64)/plugin

# Providing component specific build options to cmake
CMAKE_OPTIONS += -DBUILD_CONFIG=mysql_release
CMAKE_OPTIONS += -DINSTALL_LAYOUT=STANDALONE
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
CMAKE_OPTIONS += -DWITH_EXTRA_CHARSETS=complex
CMAKE_OPTIONS += -DENABLED_LOCAL_INFILE=ON
CMAKE_OPTIONS += -DWITH_ARCHIVE_STORAGE_ENGINE=1
CMAKE_OPTIONS += -DWITH_BLACKHOLE_STORAGE_ENGINE=1
CMAKE_OPTIONS += -DWITH_EXAMPLE_STORAGE_ENGINE=1
CMAKE_OPTIONS += -DWITH_FEDERATED_STORAGE_ENGINE=1
CMAKE_OPTIONS += -DWITH_INNOBASE_STORAGE_ENGINE=1
CMAKE_OPTIONS += '-DCOMPILATION_COMMENT=MySQL Community Server (GPL)'
CMAKE_OPTIONS += -DFEATURE_SET=community
CMAKE_OPTIONS += -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE

# Adjust '#!/usr/bin/perl'
$(INSTALL_64): PERL_SCRIPTS= \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysql_convert_table_format \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysql_find_rows \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysql_fix_extensions \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysql_setpermission \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysql_zap \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysqlaccess \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysqld_multi \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysqldumpslow \
	$(PROTO_DIR)/$(CMAKE_PREFIX)/bin/mysqlhotcopy

REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/network
