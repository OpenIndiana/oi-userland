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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		apr-util
COMPONENT_VERSION=	1.3.9
COMPONENT_PROJECT_URL=	http://apr.apache.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:20897069274a026057df26b90a6424da9d70318d930c99885c451d8753b8e4d9
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/apr/$(COMPONENT_ARCHIVE)

CONFIGURE_DEFAULT_DIRS=no

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL=0

CONFIGURE_PREFIX=/usr/apr-util/1.3

CONFIGURE_OPTIONS +=	--with-mysql=/usr/mysql/5.1
CONFIGURE_OPTIONS +=	--with-expat=/usr
CONFIGURE_OPTIONS +=	--with-sqlite3=/usr
CONFIGURE_OPTIONS +=	--with-ldap=ldap
CONFIGURE_OPTIONS +=	--without-odbc
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS.32 +=	--enable-layout=OpenSolaris
CONFIGURE_OPTIONS.64 +=	--enable-layout=OpenSolaris-$(MACH64)
CONFIGURE_OPTIONS.32 +=	--with-apr=/usr/apr/1.3/bin/apr-1-config
CONFIGURE_OPTIONS.64 +=	--with-apr=/usr/apr/1.3/bin/$(MACH64)/apr-1-config
CONFIGURE_OPTIONS.64 +=	MYSQL_CONFIG=/usr/mysql/5.1/bin/$(MACH64)/mysql_config

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin

COMPONENT_TEST_TARGETS= test

# We need this to keep doxygen happy (for include/ and docs/ contents).
COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));

# Some patches need configure script recreation.
COMPONENT_PRE_CONFIGURE_ACTION += (cd $(@D); autoconf);

# Documentation is generated in and directly packaged from 32 bit build
# directory using doxygen.
PKG_PROTO_DIRS += $(BUILD_DIR)/$(MACH32)/docs/dox/html
PKG_PROTO_DIRS += $(BUILD_DIR)/$(MACH32)/docs/dox/html/search

docs: $(BUILD_DIR)/$(MACH32)/.built
	cd $(BUILD_DIR)/$(MACH32); doxygen docs/doxygen.conf

build: $(BUILD_32_and_64) docs

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
