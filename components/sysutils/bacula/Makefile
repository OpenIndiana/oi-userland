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
# Copyright 2016 Alexander Pyhalov
# Copyright 2021 Gary Mills
# Copyright 2022 Friedrich Kink
#

BUILD_BITS=             64
USE_OPENSSL11=          yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         bacula
COMPONENT_VERSION=      13.0.0
COMPONENT_SUMMARY=      Bacula (network backup solution)
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:4119d48bbfe1518b3224a88e7365c2fa5f7d1679c815e7d15f26631883a8a0c6
COMPONENT_ARCHIVE_URL=  https://sourceforge.net/projects/bacula/files/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.bacula.org
COMPONENT_LICENSE=      AGPLv3 with exceptions
COMPONENT_LICENSE_FILE= LICENSE

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Missing files in build dir for configure without this.
# enable openldap support instead of native Solaris support
COMPONENT_PRE_CONFIGURE_ACTION =  ($(GSED) -i -e 's:with_ldap="/usr/include":with_ldap="/usr/include/openldap":' $(SOURCE_DIR)/configure ; \
				   $(GSED) -i -e '/^\#include/i \#undef __sun__' $(SOURCE_DIR)/src/plugins/dir/ldap/ldap-dir.c ; \
				   $(CLONEY) $(SOURCE_DIR) $(@D))
# To build 64-bit mysql support 
COMPONENT_POST_CONFIGURE_ACTION = ($(GSED) -i -e 's:-R /usr/mariadb/10.3/lib -L/usr/mariadb/10.3/lib:-m64 -R /usr/mariadb/10.3/lib/amd64 -L/usr/mariadb/10.3/lib/amd64:' $(@D)/src/cats/Makefile)

PATH= /usr/lib/qt/5.15/bin/amd64:/usr/mariadb/10.3/bin:/usr/postgres/12/bin:/usr/lib/qt/5.12/bin:/usr/bin:/usr/sbin

CONFIGURE_OPTIONS+= --sysconfdir=/etc/bacula
CONFIGURE_OPTIONS+= --with-scriptdir=/etc/bacula/scripts
CONFIGURE_OPTIONS+= --with-working-dir=/var/bacula
CONFIGURE_OPTIONS+= --sharedstatedir=/var/bacula
CONFIGURE_OPTIONS+= --localstatedir=/var/bacula
CONFIGURE_OPTIONS+= --with-logdir=/var/bacula
CONFIGURE_OPTIONS+= --with-pid-dir=/var/bacula
CONFIGURE_OPTIONS+= --with-smtp-host=localhost
CONFIGURE_OPTIONS+= --with-sqlite3
CONFIGURE_OPTIONS+= --with-postgresql=/usr/postgres/12
CONFIGURE_OPTIONS+= --with-mysql=/usr/mariadb/10.3
CONFIGURE_OPTIONS+= --with-openssl
CONFIGURE_OPTIONS+= --with-ldap
CONFIGURE_OPTIONS+= --enable-ldap-bpam
CONFIGURE_OPTIONS+= --enable-smartalloc 
CONFIGURE_OPTIONS+= --enable-largefile
CONFIGURE_OPTIONS+= --with-tcp-wrappers
CONFIGURE_OPTIONS+= --enable-conio
#CONFIGURE_OPTIONS+= --enable-bat
CONFIGURE_OPTIONS+= --enable-readline
CONFIGURE_OPTIONS+= --disable-afs
CONFIGURE_OPTIONS+= --disable-rpath

CONFIGURE_OPTIONS+= LDFLAGS="-m64 -L$(OPENSSL_PREFIX)/lib/$(MACH64) -lssl -lcrypto -L/lib/$(MACH64) -L/usr/lib/$(MACH64) -lldap_r"
CONFIGURE_OPTIONS+= CPPFLAGS="$(CPP_LARGEFILES) -m64 -I$(OPENSSL_PREFIX)/include -I/usr/include/openldap -I/usr/include/readline"
CONFIGURE_OPTIONS+= CXXFLAGS="$(CPPFLAGS) -m64"
CONFIGURE_OPTIONS+= PKG_CONFIG_PATH=/usr/lib/qt/5.15/lib/amd64/pkgconfig

# manually added dependencies
REQUIRED_PACKAGES += database/mariadb-103
REQUIRED_PACKAGES += database/mariadb-103/client
REQUIRED_PACKAGES += database/postgres-12/developer
REQUIRED_PACKAGES += library/openldap

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/mariadb-103/library
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/lzo
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
