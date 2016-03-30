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
COMPONENT_VERSION     = 5.6.25
COMPONENT_ARCHIVE_HASH= \
         sha256:15079c0b83d33a092649cbdf402c9225bcd3f33e87388407be5cdbf1432c7fbd
COMPONENT_ARCHIVE_URL = http://cdn.mysql.com/Downloads/MySQL-5.6/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://dev.mysql.com/ 
COMPONENT_BUGDB       = database/mysql

BUILD_STYLE= justmake
TEST_TARGET= $(NO_TESTS)
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
CMAKE_CFLAGS.32     = -D__MATHERR_RENAME_EXCEPTION
CMAKE_CFLAGS.64     = -m64 -D__MATHERR_RENAME_EXCEPTION
CMAKE_CXXFLAGS.32   = -D__MATHERR_RENAME_EXCEPTION -template=extdef -xnorunpath
CMAKE_CXXFLAGS.64   = -m64 -D__MATHERR_RENAME_EXCEPTION -template=extdef -xnorunpath

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
CMAKE_OPTIONS += -DWITH_INNOBASE_STORAGE_ENGINE=1
CMAKE_OPTIONS += -DCMAKE_CXX_COMPILER=$(CXX)
CMAKE_OPTIONS += -DCMAKE_C_COMPILER=$(CC)
CMAKE_OPTIONS += -DCMAKE_C_FLAGS="$(CMAKE_CFLAGS.$(BITS))"
CMAKE_OPTIONS += -DCMAKE_CXX_FLAGS="$(CMAKE_CXXFLAGS.$(BITS))"
CMAKE_OPTIONS += '-DCOMPILATION_COMMENT=MySQL Community Server (GPL)'
CMAKE_OPTIONS += -DFEATURE_SET=community
CMAKE_OPTIONS += -DSUNPRO_CXX_LIBRARY=stdcxx4

COMPONENT_PRE_BUILD_ACTION += cd $(@D);
COMPONENT_PRE_BUILD_ACTION += export LDFLAGS=$(CMAKE_CXXFLAGS.$(BITS));
COMPONENT_PRE_BUILD_ACTION += echo Running cmake with $(CMAKE_OPTIONS);
COMPONENT_PRE_BUILD_ACTION += $(CMAKE) . $(CMAKE_OPTIONS);

REQUIRED_PACKAGES += database/mysql-56/client
REQUIRED_PACKAGES += developer/build/cmake
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/perl-512
REQUIRED_PACKAGES += runtime/perl-520
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/network
REQUIRED_PACKAGES += library/c++/stdcxx
