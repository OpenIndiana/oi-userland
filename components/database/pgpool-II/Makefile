#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Alexander Pyhalov
#

BUILD_BITS= 64
USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	pgpool-II
COMPONENT_VERSION= 	4.4.3
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= 	A connection pooling/replication server for PostgreSQL
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:46745aa98f454e097cecb4dacf536f89c37ed3ec41f32f0a846934229d0eb733
COMPONENT_PROJECT_URL=	https://www.pgpool.net
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/download.php?f=$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	database/postgres/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

include $(WS_MAKE_RULES)/common.mk

CFLAGS += -D__EXTENSIONS__ -I/usr/include/openldap

COMPONENT_PREP_ACTION = ( cd $(SOURCE_DIR) && autoreconf -fi )
COMPONENT_PRE_CONFIGURE_ACTION = ( cp -a $(SOURCE_DIR)/* $(@D) )
COMPONENT_POST_CONFIGURE_ACTION = ( find $(@D) -name Makefile -exec $(GSED) -i -e 's/lldap /lldap-2.6 /' {} \; )

CONFIGURE_BINDIR = $(CONFIGURE_PREFIX)/bin

# Earlier all binaries were delivered in /usr/bin,
# preserve this behavior
CONFIGURE_SBINDIR = $(CONFIGURE_PREFIX)/bin

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS += --sysconfdir=/etc/pgpool-II
CONFIGURE_OPTIONS += --with-ldap
CONFIGURE_OPTIONS += --with-pam
CONFIGURE_OPTIONS += --with-openssl
CONFIGURE_OPTIONS += LDFLAGS=-L$(OPENSSL_PREFIX)/lib/$(MACH64)
CONFIGURE_OPTIONS += CPPFLAGS=-I$(OPENSSL_PREFIX)/include

COMPONENT_POST_BUILD_ACTION += $(ENV) $(COMPONENT_BUILD_ENV) \
	$(GMAKE) $(COMPONENT_BUILD_GMAKE_ARGS) -C $(BUILD_DIR_$(BITS))/doc/src/sgml man1 man8

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTO_DIR)/usr/share/man && \
	$(CP) -r $(BUILD_DIR_$(BITS))/doc/src/sgml/man[18] \
		$(PROTO_DIR)/usr/share/man

# Build dependencies
REQUIRED_PACKAGES += data/docbook/dtds
REQUIRED_PACKAGES += developer/documentation-tool/openjade

# Auto-generated dependencies
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
