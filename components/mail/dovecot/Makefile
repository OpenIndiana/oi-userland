#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022-2026 Friedrich Kink
# Copyright 2023 Niklas Poslovski
# Copyright 2025 Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         dovecot
COMPONENT_VERSION=      2.4.5
COMPONENT_SUMMARY=      DOVECOT - The Secure IMAP server
COMPONENT_DESCRIPTION=	Dovecot is an open source IMAP and POP3 email server for \
		Linux/UNIX-like systems, written with security primarily in mind. \
		Dovecot is an excellent choice for both small and large installations. \
		It's fast, simple to set up, requires no special administration \
		and it uses very little memory.
COMPONENT_PROJECT_URL=  https://dovecot.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/releases/2.4/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:868c2686a61b5f8e00a3e4721789b1ab46e6528fd773a5fbed07a6ecba7731e6
COMPONENT_FMRI=         mail/dovecot
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE=      MIT,LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV += PANDOC=false
CONFIGURE_ENV += CPPFLAGS="-I$(OPENSSL_INCDIR)"

PATH = $(PATH.gnu):$(MYSQL_BINDIR)

COMPONENT_POST_CONFIGURE_ACTION = ( $(GSED) -i -e 's|^\#IMAP_HIBERNATE|IMAP_HIBERNATE|' $(@D)/src/Makefile )

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --libexecdir=/usr/lib
CONFIGURE_OPTIONS += --without-gssapi
#CONFIGURE_OPTIONS += --with-gssapi=plugin
CONFIGURE_OPTIONS += --with-ldap=plugin
CONFIGURE_OPTIONS += --with-sql=plugin
CONFIGURE_OPTIONS += --with-lua=plugin
CONFIGURE_OPTIONS += --with-ioloop=poll
CONFIGURE_OPTIONS += --with-notify=none
CONFIGURE_OPTIONS += --with-sodium
CONFIGURE_OPTIONS += --with-ssldir=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS += --with-sql=plugin
CONFIGURE_OPTIONS += --with-mysql
CONFIGURE_OPTIONS += --with-pgsql
CONFIGURE_OPTIONS += --with-sqlite
CONFIGURE_OPTIONS += --enable-year2038
CONFIGURE_OPTIONS += --enable-static=no
CONFIGURE_OPTIONS += --without-systemd
CONFIGURE_OPTIONS += LDAP_LIBS="-lldap_r"
CONFIGURE_OPTIONS += SSL_LIBS="-L$(OPENSSL_LIBDIR) -lssl -lcrypto"
CONFIGURE_OPTIONS += CPPFLAGS="-I$(OPENSSL_INCDIR) -I/usr/include/kerberosv5 -I/usr/include/openldap -I/usr/include/gssapi"
CONFIGURE_OPTIONS += CFLAGS="-Wno-incompatible-pointer-types -D__EXTENSIONS__ -DBUILD_IMAP_HIBERNATE"
#CONFIGURE_OPTIONS += CFLAGS="-std=c17 -Wno-incompatible-pointer-types -D__EXTENSIONS__ -DBUILD_IMAP_HIBERNATE"
CONFIGURE_OPTIONS += PGSQL_LIBS="-L$(PG_LIBDIR) -lpq"
CONFIGURE_OPTIONS += PGSQL_CFLAGS="-I$(PG_INCDIR)"
CONFIGURE_OPTIONS += MARIADB_LIBS="-L$(MYSQL_LIBDIR) -lmariadb"
CONFIGURE_OPTIONS += MARIADB_CFLAGS="-I$(MYSQL_INCDIR)"

# python interpreter
COMPONENT_POST_INSTALL_ACTION += ( \
        $(GSED) -i -e '1 s:\#!/usr/bin/env python[0-9.]*:\#!/usr/bin/python$(PYTHON_VERSION):' \
        $(PROTOUSRLIBDIR)/dovecot/settings-history.py ; \
        /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(MYSQL_LIBDIR)"' $(PROTOUSRDIR)/lib/$(MACH64)/dovecot/libdriver_mysql.so ; \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH "$(MYSQL_LIBDIR)"' $(PROTOUSRDIR)/lib/$(MACH64)/dovecot/libdriver_mysql.so; \
        /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(PG_LIBDIR)"' $(PROTOUSRDIR)/lib/$(MACH64)/dovecot/libdriver_pgsql.so ; \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH "$(PG_LIBDIR)"' $(PROTOUSRDIR)/lib/$(MACH64)/dovecot/libdriver_pgsql.so; )

COMPONENT_TEST_ARGS+=   -k
COMPONENT_TEST_TRANSFORMS = \
	'-n ' \
	'-e "/: ok$$/p" ' \
	'-e "/tests failed$$/p" ' \
	'-e "/: FAILED$$/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += library/lz4
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += library/xapian
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua-54
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES.python += runtime/python
