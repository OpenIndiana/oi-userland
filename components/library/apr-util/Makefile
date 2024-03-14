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
# Copyright (c) 2020, Andreas Wacknitz
# Copyright (c) 2023, Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		apr-util
COMPONENT_VERSION=	1.6.3
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	https://apr.apache.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:2b74d8932703826862ca305b094eef2983c27b39d5c9414442e9976a9acf1983
COMPONENT_ARCHIVE_URL=	https://archive.apache.org/dist/apr/$(COMPONENT_ARCHIVE)

CONFIGURE_DEFAULT_DIRS=no

include $(WS_MAKE_RULES)/common.mk

# Without this the build is unable to find right C preprocessor
PATH = $(GCC_BINDIR):$(PATH.illumos)

PATCH_LEVEL=0

CONFIGURE_PREFIX=/usr/apr-util

CONFIGURE_OPTIONS +=	--with-mysql=$(MYSQL_HOME)
CONFIGURE_OPTIONS +=	MYSQL_CONFIG=$(MYSQL_CONFIG)
CONFIGURE_OPTIONS +=	--with-pgsql=$(PG_HOME)
CONFIGURE_OPTIONS +=	--with-expat=/usr
CONFIGURE_OPTIONS +=	--with-sqlite3=/usr
CONFIGURE_OPTIONS +=	--with-ldap=ldap_r-2.4
CONFIGURE_OPTIONS +=	--with-ldap-include=/usr/include/openldap
CONFIGURE_OPTIONS +=	--without-odbc
CONFIGURE_OPTIONS +=	--enable-layout=OpenSolaris-$(MACH64)
CONFIGURE_OPTIONS +=	--with-apr=/usr/apr/bin/apr-1-config
CONFIGURE_OPTIONS +=	--bindir=$(CONFIGURE_PREFIX)/bin
CONFIGURE_OPTIONS +=	PGSQL_CONFIG=$(PG_CONFIG.64)

COMPONENT_TEST_TARGETS= test

COMPONENT_TEST_TRANSFORMS += \
    '-e "/^teststatus=0;/,/make\[2\]: Leaving directory/p" ' \
    '-e "/.*/d" '

COMPONENT_PREP_ACTION += (cd $(@D) && autoreconf -fi)

# We need this to keep doxygen happy (for include/ and docs/ contents).
COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# We need to list (the default) 'all' build target explicitly because we need
# to add one more (non-default) target
COMPONENT_BUILD_TARGETS += all
# The 'dox' target is used to build documentation
COMPONENT_BUILD_TARGETS += dox

# Install documentation
COMPONENT_POST_INSTALL_ACTION += $(CP) -a $(@D)/docs/dox/manual $(PROTO_DIR)/usr/apr-util/manual ;

# Build dependencies
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
# The MariaDB client must be installed to get mysql_config:
REQUIRED_PACKAGES += $(MYSQL_CLIENT_PKG)
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/apr
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
