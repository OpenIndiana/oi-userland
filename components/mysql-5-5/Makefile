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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME        = mysql
COMPONENT_VERSION     = 5.5.31
COMPONENT_SRC         = $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE     = $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:9cdd650b47e3ea864ab40d4ab23fa4a9fdfabc7fd018bf5c9cce30722c0abcea
COMPONENT_ARCHIVE_URL = http://downloads.mysql.com/archives/mysql-5.5/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://dev.mysql.com/ 
COMPONENT_BUGDB       = database/mysql

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

# Enable ASLR for this component
ASLR_MODE           = $(ASLR_ENABLE)

# This component uses cmake to generate Makefiles and thus does not
# run any configure script
CMAKE               = $(shell which cmake)
CMAKE_PREFIX        = /usr/mysql/5.5
CONFDIR             = /etc/mysql/5.5
DATA_PREFIX         = /var/mysql/5.5

CMAKE_BINDIR.32     = bin/$(MACH32)
CMAKE_BINDIR.64     = bin
CMAKE_LIBDIR.32     = lib
CMAKE_LIBDIR.64     = lib/$(MACH64)
CMAKE_PLUGINDIR.32  = lib/plugin
CMAKE_PLUGINDIR.64  = lib/$(MACH64)/plugin
CMAKE_CFLAGS.64     = -m64
CMAKE_CXXFLAGS.64   = -m64

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
CMAKE_OPTIONS += -DWITH_EXTRA_CHARSETS=complex
CMAKE_OPTIONS += -DENABLED_LOCAL_INFILE=ON
CMAKE_OPTIONS += -DWITH_ARCHIVE_STORAGE_ENGINE=1
CMAKE_OPTIONS += -DWITH_BLACKHOLE_STORAGE_ENGINE=1
CMAKE_OPTIONS += -DWITH_EXAMPLE_STORAGE_ENGINE=1
CMAKE_OPTIONS += -DWITH_FEDERATED_STORAGE_ENGINE=1
CMAKE_OPTIONS += -DWITH_INNOBASE_STORAGE_ENGINE=1
CMAKE_OPTIONS += -DCMAKE_C_FLAGS=$(CMAKE_CFLAGS.$(BITS))
CMAKE_OPTIONS += -DCMAKE_CXX_FLAGS=$(CMAKE_CXXFLAGS.$(BITS))
CMAKE_OPTIONS += '-DCOMPILATION_COMMENT=MySQL Community Server (GPL)'
CMAKE_OPTIONS += -DFEATURE_SET=community

COMPONENT_PRE_BUILD_ACTION += cd $(@D);
COMPONENT_PRE_BUILD_ACTION += export LDFLAGS=$(CMAKE_CXXFLAGS.$(BITS));
COMPONENT_PRE_BUILD_ACTION += echo Running cmake with $(CMAKE_OPTIONS);
COMPONENT_PRE_BUILD_ACTION += $(CMAKE) . $(CMAKE_OPTIONS);

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
