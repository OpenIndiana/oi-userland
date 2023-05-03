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

USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         bacula
COMPONENT_VERSION=      13.0.3
COMPONENT_SUMMARY=      Bacula (network backup solution)
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:0949c32be1090585e88e4c01d828002e87603136d87c598a29dff42bb3ed2a40
COMPONENT_ARCHIVE_URL=  https://sourceforge.net/projects/bacula/files/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.bacula.org
COMPONENT_LICENSE=      AGPLv3 with exceptions
COMPONENT_LICENSE_FILE= LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Missing files in build dir for configure without this.
# enable openldap support instead of native Solaris support
COMPONENT_PRE_CONFIGURE_ACTION =  ($(GSED) -i -e 's:with_ldap="/usr/include":with_ldap="/usr/include/openldap":' $(SOURCE_DIR)/configure ; \
				   $(GSED) -i -e '/^\#include/i \#undef __sun__' $(SOURCE_DIR)/src/plugins/dir/ldap/ldap-dir.c ; \
				   $(CLONEY) $(SOURCE_DIR) $(@D))
# This is an ugly hack. Bacula doesn't find our 64 bit mariadb libraries and tries to use a 32 bit static library instead. We fix the Makefile after its creation:
COMPONENT_POST_CONFIGURE_ACTION = ($(GSED) -i -e 's:/usr/mariadb/10.6/lib/mysql/libmysqlclient_r.a:-m64 -R $(MYSQL_LIBDIR) -L$(MYSQL_LIBDIR) -lmariadb:' $(@D)/src/cats/Makefile)

PATH= $(QT5_BINDIR):$(MYSQL_BINDIR):$(PG_BINDIR):$(PATH.illumos)

CONFIGURE_OPTIONS+= --sysconfdir=/etc/bacula
CONFIGURE_OPTIONS+= --with-scriptdir=/etc/bacula/scripts
CONFIGURE_OPTIONS+= --with-working-dir=/var/bacula
CONFIGURE_OPTIONS+= --sharedstatedir=/var/bacula
CONFIGURE_OPTIONS+= --localstatedir=/var/bacula
CONFIGURE_OPTIONS+= --with-logdir=/var/bacula
CONFIGURE_OPTIONS+= --with-pid-dir=/var/bacula
CONFIGURE_OPTIONS+= --with-smtp-host=localhost
CONFIGURE_OPTIONS+= --with-sqlite3
CONFIGURE_OPTIONS+= --with-postgresql=$(PG_HOME)
CONFIGURE_OPTIONS+= --with-mysql=$(MYSQL_HOME)
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

CONFIGURE_OPTIONS+= LDFLAGS="-m64 -L$(OPENSSL_LIBDIR) -lssl -lcrypto -L/lib/$(MACH64) -L/usr/lib/$(MACH64) -lldap_r"
CONFIGURE_OPTIONS+= CPPFLAGS="$(CPP_LARGEFILES) -m64 -I$(OPENSSL_INCDIR) -I/usr/include/openldap -I/usr/include/readline"
CONFIGURE_OPTIONS+= CXXFLAGS="$(CPPFLAGS) -m64"
CONFIGURE_OPTIONS+= PKG_CONFIG_PATH=$(QT5_PKG_CONFIG_PATH)

# manually added dependencies
REQUIRED_PACKAGES += $(MYSQL_BASEPKG)
REQUIRED_PACKAGES += $(MYSQL_BASEPKG)/client
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)
REQUIRED_PACKAGES += library/openldap

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/lzo
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
