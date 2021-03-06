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
#
BUILD_BITS=			32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		apr-util
COMPONENT_VERSION=	1.6.1
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	https://apr.apache.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:b65e40713da57d004123b6319828be7f1273fbc6490e145874ee1177e112c459
COMPONENT_ARCHIVE_URL=	https://archive.apache.org/dist/apr/$(COMPONENT_ARCHIVE)

CONFIGURE_DEFAULT_DIRS=no

include $(WS_MAKE_RULES)/common.mk

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
CONFIGURE_OPTIONS.32 +=	--enable-layout=OpenSolaris
CONFIGURE_OPTIONS.64 +=	--enable-layout=OpenSolaris-$(MACH64)
CONFIGURE_OPTIONS.32 +=	--with-apr=/usr/apr/bin/apr-1-config
CONFIGURE_OPTIONS.64 +=	--with-apr=/usr/apr/bin/$(MACH64)/apr-1-config
CONFIGURE_OPTIONS.64 +=	PGSQL_CONFIG=$(PG_CONFIG.64)

COMPONENT_TEST_TARGETS= test

COMPONENT_TEST_TRANSFORMS += \
    '-e "/^teststatus=0;/,/make\[2\]: Leaving directory/p" ' \
    '-e "/.*/d" '

COMPONENT_PREP_ACTION += (cd $(@D) && autoreconf -fi)

# We need this to keep doxygen happy (for include/ and docs/ contents).
COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Documentation is generated in and directly packaged from 32 bit build
# directory using doxygen.
PKG_PROTO_DIRS += $(BUILD_DIR)/$(MACH32)/docs/dox/manual

COMPONENT_POST_INSTALL_ACTION.32=\
	(cd $(BUILD_DIR)/$(MACH32); doxygen docs/doxygen.conf)
COMPONENT_POST_INSTALL_ACTION=$(COMPONENT_POST_INSTALL_ACTION.$(BITS))

# Build dependencies
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
# The MariaDB client must be installed to get mysql_config:
REQUIRED_PACKAGES += database/mariadb-101/client

# Auto-generated dependencies
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/mariadb-101/library
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/apr
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += system/library
