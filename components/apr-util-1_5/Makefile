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
# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
#

# Prefer 32-bit over 64-bit as apr-util has its own custom package layout.
BUILD_BITS= 32_and_64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		apr-util
COMPONENT_VERSION=	1.5.4
COMPONENT_PROJECT_URL=	http://apr.apache.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:976a12a59bc286d634a21d7be0841cc74289ea9077aa1af46be19d1a6e844c19
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/apr/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/apache

TPNO=			20776

CONFIGURE_DEFAULT_DIRS=no
include $(WS_MAKE_RULES)/common.mk

# Micro version for easy libraries packaging
MICRO_VERSION:= $(shell echo $(COMPONENT_VERSION) | awk -F. '{ print $$3 }')
PKG_MACROS+= MICRO_VERSION=$(MICRO_VERSION)

PATCH_LEVEL=0

CONFIGURE_PREFIX=$(USRDIR)/apr-util/1.5

ifeq ($(BUILD_TYPE), evaluation)
CONFIGURE_OPTIONS +=	--with-mysql=$(USRDIR)/mysql/5.5
else
CONFIGURE_OPTIONS.64 +=	--with-mysql=$(USRDIR)/mysql/5.7
endif
CONFIGURE_OPTIONS +=	--with-expat=$(USRDIR)
CONFIGURE_OPTIONS +=	--with-sqlite3=$(USRDIR)
CONFIGURE_OPTIONS +=	--with-ldap=ldap_r-2.4
CONFIGURE_OPTIONS +=	--with-ldap-include=$(USRINCDIR)/openldap
CONFIGURE_OPTIONS +=	--without-odbc
CONFIGURE_OPTIONS.32 +=	--enable-layout=Solaris
CONFIGURE_OPTIONS.64 +=	--enable-layout=Solaris-$(MACH64)
CONFIGURE_OPTIONS.32 +=	--with-apr=$(USRDIR)/apr/1.5/bin/apr-1-config
CONFIGURE_OPTIONS.64 +=	--with-apr=$(USRDIR)/apr/1.5/bin/$(MACH64)/apr-1-config
ifeq ($(BUILD_TYPE), evaluation)
CONFIGURE_OPTIONS.32 +=	MYSQL_CONFIG=$(USRDIR)/mysql/5.5/bin/$(MACH32)/mysql_config
endif

ifeq   ($(strip $(PARFAIT_BUILD)),yes)
PATH=$(PARFAIT_TOOLS):$(SPRO_VROOT)/bin:$(USRBINDIR):$(GNUBIN)
else
PATH=$(SPRO_VROOT)/bin:$(USRBINDIR):$(GNUBIN)
endif

COMPONENT_TEST_TARGETS= test

$(INSTALL_64): COMPONENT_POST_INSTALL_ACTION += \
        cd $(SOURCE_DIR); \
        sed 's;OUTPUT_DIRECTORY=.*;OUTPUT_DIRECTORY=$(PROTO_DIR)$(CONFIGURE_PREFIX);' \
          docs/doxygen.conf | doxygen - ;

# Some patches need configure script recreation.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fi);

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

ifeq ($(BUILD_TYPE), evaluation)
REQUIRED_PACKAGES += database/mysql-55
REQUIRED_PACKAGES += database/mysql-55/library
else
REQUIRED_PACKAGES += database/mysql-57
REQUIRED_PACKAGES += database/mysql-57/library
endif
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += library/apr-15
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/network/ldap/openldap
