
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
# Copyright (c) 2024, Friedrich Kink
#

include ../../../make-rules/shared-macros.mk

OPENSSL_VERSION= 3.1

COMPONENT_NAME=		freeradius
COMPONENT_VERSION=	3.2.5
COMPONENT_SUMMARY=	The FreeRADIUS server
COMPONENT_DESCRIPTION=	The FreeRADIUS Server Project is a high performance and highly \
		configurable multi-protocol policy server, supporting RADIUS, DHCPv4 DHCPv6, DNS, \
		TACACS+ and VMPS. Using RADIUS allows authentication and authorization for a \
		network to be centralized, and minimizes the number of changes that have to be \
		done when adding or deleting new users to a network.
COMPONENT_SRC=		$(COMPONENT_NAME)-server-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://freeradius.org/
COMPONENT_ARCHIVE_HASH=	sha256:1e75f5fc1961d9854d1cb3c6921612fbe2b9edb8ee508a5a7cbd69f1e7607115
COMPONENT_ARCHIVE_URL=	https://github.com/FreeRADIUS/$(COMPONENT_NAME)-server/releases/download/release_3_2_5/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		network/radius
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

TEST_TARGET= $(NO_TESTS)

COMPONENT_PRE_CONFIGURE_ACTION += ( \
        $(CLONEY) $(SOURCE_DIR) $(@D); \
        );

CONFIGURE_OPTIONS += CFLAGS="-D_XPG4_2 -I$(OPENSSL_INCDIR) -I/usr/include/openldap -I/usr/include/odbc -I/usr/postgres/$(PG_VERSION)/include"
CONFIGURE_OPTIONS += LDFLAGS="-lldap_r -L$(OPENSSL_LIBDIR)"
CONFIGURE_OPTIONS += --srcdir=$(BUILD_DIR)/$(MACH64)
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --without-static-modules

COMPONENT_INSTALL_ARGS +=       R=$(PROTO_DIR)
COMPONENT_POST_INSTALL_ACTION =  \
	/usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(MYSQL_LIBDIR)"' $(PROTOUSRLIBDIR64)/rlm_sql_mysql.so ; \
	/usr/bin/elfedit -e 'dyn:value -s  RPATH "$(MYSQL_LIBDIR)"' $(PROTOUSRLIBDIR64)/rlm_sql_mysql.so ; \
	/usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(GCC_LIBDIR)"' $(PROTOUSRLIBDIR64)/rlm_sql_unixodbc.so ; \
	/usr/bin/elfedit -e 'dyn:value -s  RPATH "$(GCC_LIBDIR)"' $(PROTOUSRLIBDIR64)/rlm_sql_unixodbc.so ; \
	/usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(PG_LIBDIR)"' $(PROTOUSRLIBDIR64)/rlm_sql_postgresql.so ; \
	/usr/bin/elfedit -e 'dyn:value -s  RPATH "$(PG_LIBDIR)"' $(PROTOUSRLIBDIR64)/rlm_sql_postgresql.so ; \
	/usr/bin/elfedit -e 'dyn:delete NEEDED' $(PROTOUSRLIBDIR64)/rlm_python.so ; \
	/usr/bin/elfedit -e 'dyn:value -s  NEEDED "libpython$(PYTHON_VERSION).so.1.0"' $(PROTOUSRLIBDIR64)/rlm_python.so ; \
	/usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(GCC_LIBDIR):$(USRLIBDIR)/python$(PYTHON_VERSION)/config-$(PYTHON_VERSION)"' $(PROTOUSRLIBDIR64)/rlm_python.so ; \
	/usr/bin/elfedit -e 'dyn:value -s  RPATH "$(GCC_LIBDIR):$(USRLIBDIR)/python$(PYTHON_VERSION)/config-$(PYTHON_VERSION)"' $(PROTOUSRLIBDIR64)/rlm_python.so ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/freetds
REQUIRED_PACKAGES += library/json-c
REQUIRED_PACKAGES += library/libmemcached
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/talloc
REQUIRED_PACKAGES += library/unixodbc
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += web/curl
