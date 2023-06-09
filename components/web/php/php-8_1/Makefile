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
# Copyright 2013, EveryCity Ltd. All rights reserved.
# Copyright 2022 Friedrich Kink. All rights reserved.
# Copyright 2022 Niklas Poslovski
#

USE_OPENSSL11=		yes
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=         php
COMPONENT_MJR_VERSION=	8.1
COMPONENT_MNR_VERSION=	19
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      PHP 8.1
COMPONENT_DESCRIPTION=	PHP is a popular general-purpose scripting language that is especially suited to web development.
COMPONENT_VERSION=      $(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_PROJECT_URL=  https://www.php.net/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:0ebb6b0ecf5d8e355c2f1362807f9b73c6e803d496c5ad3e4fb00be989988372
COMPONENT_ARCHIVE_URL=  https://www.php.net/distributions/$(COMPONENT_ARCHIVE)
#COMPONENT_SIG_URL=	https://www.php.net/distributions/$(COMPONENT_ARCHIVE).asc
COMPONENT_FMRI=         web/$(COMPONENT_NAME)-81
COMPONENT_CLASSIFICATION=Meta Packages/Group Packages
COMPONENT_LICENSE=      PHP License
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

MYSQL_DIR=		$(MYSQL_HOME)

# Apache Paths
AP_PREFIX=		/usr/apache2/2.4
AP_SYSCONFDIR=	/etc/apache2/2.4

# PHP Paths
PHP_PREFIX=		/usr/php/$(COMPONENT_MJR_VERSION)
PHP_SYSCONFDIR=	/etc/php/$(COMPONENT_MJR_VERSION)
PHP_DATADIR=	/var/php/$(COMPONENT_MJR_VERSION)

# -D__solaris__ is very important to trigger patched file TSRM.h
# otherwise mod_php81.so is crashing
CFLAGS +=        $(CC_BITS) -D_XPG4_2 -D__EXTENSIONS__ -D__solaris__
CFLAGS +=		-I/usr/include/openldap
CPPFLAGS +=      $(CPP_XPG6MODE)
LDFLAGS +=       -lldap_r
CPPFLAGS +=      -I$(MYSQL_INCDIR)
CFLAGS +=        -I$(MYSQL_INCDIR)
LDFLAGS +=       -L$(MYSQL_LIBDIR)

# build with the system default libjpeg
CFLAGS+=                $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS+=              $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
CPPFLAGS+=              $(JPEG_CPPFLAGS)
LDFLAGS+=               $(JPEG_LDFLAGS)

# Configure Options
CONFIGURE_OPTIONS =  --prefix=$(PHP_PREFIX)
CONFIGURE_OPTIONS += --bindir=$(PHP_PREFIX)/bin
CONFIGURE_OPTIONS += --sbindir=$(PHP_PREFIX)/bin
CONFIGURE_OPTIONS += --libdir=$(PHP_PREFIX)/lib/$(MACH64)
CONFIGURE_OPTIONS += --libexecdir=$(PHP_PREFIX)/libexec
CONFIGURE_OPTIONS += --includedir=$(PHP_PREFIX)/include
CONFIGURE_OPTIONS += --sysconfdir=$(PHP_SYSCONFDIR)
CONFIGURE_OPTIONS += --datadir=$(PHP_DATADIR)
CONFIGURE_OPTIONS += --mandir=$(PHP_PREFIX)/share/man
CONFIGURE_OPTIONS += --localstatedir=$(PHP_DATADIR)
CONFIGURE_OPTIONS += OPENSSL_CFLAGS=-I$(OPENSSL_INCDIR)
CONFIGURE_OPTIONS += OPENSSL_LIBS="-L$(OPENSSL_LIBDIR) -lssl -lcrypto"
CONFIGURE_OPTIONS += KERBEROS_CFLAGS=-I/usr/include/kerberosv5
CONFIGURE_OPTIONS += KERBEROS_LIBS="-L/usr/lib/$(MACH64) -lgss -lkrb5"
CONFIGURE_OPTIONS += PCRE2_CFLAGS="-I/usr/include/pcre"
CONFIGURE_OPTIONS += ODBC_CFLAGS="-I/usr/include/odbc"

# SAPI modules
CONFIGURE_OPTIONS += --with-apxs2=$(AP_PREFIX)/bin/apxs
CONFIGURE_OPTIONS += --enable-fpm

ifeq ($(strip $(MACH)),i386)
CONFIGURE_OPTIONS += --build=x86_64-pc-solaris$(SOLARIS_VERSION)
CONFIGURE_OPTIONS += --with-external-pcre
else
CONFIGURE_OPTIONS += --build=sparcv9-solaris$(SOLARIS_VERSION)
CONFIGURE_OPTIONS += --with-pcre-jit=no
endif

CONFIGURE_OPTIONS += --with-config-file-path=$(PHP_SYSCONFDIR)
CONFIGURE_OPTIONS += --with-config-file-scan-dir=$(PHP_SYSCONFDIR)/conf.d
CONFIGURE_OPTIONS += --with-pear=$(PHP_PREFIX)/share/PEAR

CONFIGURE_OPTIONS += --with-layout=PHP

CONFIGURE_OPTIONS += --with-cdb
CONFIGURE_OPTIONS += --with-kerberos
CONFIGURE_OPTIONS += --with-readline
CONFIGURE_OPTIONS += --enable-dtrace

# Shared Extensions
CONFIGURE_OPTIONS += --with-gettext=shared
CONFIGURE_OPTIONS += --with-zlib=shared
CONFIGURE_OPTIONS += --with-openssl=shared
CONFIGURE_OPTIONS += --with-pdo-sqlite=shared
CONFIGURE_OPTIONS += --with-ldap=shared
CONFIGURE_OPTIONS += --with-bz2=shared
CONFIGURE_OPTIONS += --with-iconv=shared
CONFIGURE_OPTIONS += --with-tidy=shared
CONFIGURE_OPTIONS += --with-mhash=shared
CONFIGURE_OPTIONS += --with-xsl=shared
CONFIGURE_OPTIONS += --with-curl=shared
CONFIGURE_OPTIONS += --with-pspell=shared
CONFIGURE_OPTIONS += --with-imap=shared
CONFIGURE_OPTIONS += --with-imap-ssl
CONFIGURE_OPTIONS += --with-zip=shared
CONFIGURE_OPTIONS += --with-sodium=shared
CONFIGURE_OPTIONS += --enable-bcmath=shared
CONFIGURE_OPTIONS += --enable-ctype=shared
CONFIGURE_OPTIONS += --enable-calendar=shared
CONFIGURE_OPTIONS += --enable-tokenizer=shared
CONFIGURE_OPTIONS += --enable-exif=shared
CONFIGURE_OPTIONS += --enable-dom=shared
CONFIGURE_OPTIONS += --enable-ftp=shared
CONFIGURE_OPTIONS += --enable-intl=shared
CONFIGURE_OPTIONS += --enable-pdo=shared
CONFIGURE_OPTIONS += --enable-mbstring=shared
CONFIGURE_OPTIONS += --enable-xmlreader=shared
CONFIGURE_OPTIONS += --enable-xmlwriter=shared
CONFIGURE_OPTIONS += --enable-soap=shared
CONFIGURE_OPTIONS += --enable-sockets=shared
CONFIGURE_OPTIONS += --enable-mysqlnd=shared
CONFIGURE_OPTIONS += --with-snmp=shared

# Extensions, dependent on other packages

CONFIGURE_OPTIONS += --with-mysqli=shared,$(MYSQL_BINDIR)/mysql_config
CONFIGURE_OPTIONS += --with-pdo-mysql=shared,$(MYSQL_DIR)
CONFIGURE_OPTIONS += --with-pgsql=shared,$(PG_BINDIR)
CONFIGURE_OPTIONS += --with-pdo-pgsql=shared,$(PG_BINDIR)

# Disabled extensions & Options
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-dba
CONFIGURE_OPTIONS += --disable-debug
CONFIGURE_OPTIONS += --disable-libgcc
CONFIGURE_OPTIONS += --without-dbm

# Enabled extensions
CONFIGURE_OPTIONS += --enable-zts
CONFIGURE_OPTIONS += --enable-re2c-cgoto
CONFIGURE_OPTIONS += --enable-cli
CONFIGURE_OPTIONS += --enable-cgi
CONFIGURE_OPTIONS += --with-ffi
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-filter
CONFIGURE_OPTIONS += --enable-gd-jis-conv
CONFIGURE_OPTIONS += --enable-short-tags
CONFIGURE_OPTIONS += --enable-pcntl
CONFIGURE_OPTIONS += --enable-shmop
CONFIGURE_OPTIONS += --enable-sysvmsg
CONFIGURE_OPTIONS += --enable-sysvsem
CONFIGURE_OPTIONS += --enable-sysvshm
CONFIGURE_OPTIONS += --enable-simplexml
CONFIGURE_OPTIONS += --enable-session
CONFIGURE_OPTIONS += --enable-opcache
CONFIGURE_OPTIONS += --with-mhash
CONFIGURE_OPTIONS += --enable-gd
CONFIGURE_OPTIONS += --with-external-gd
CONFIGURE_OPTIONS += --with-webp
CONFIGURE_OPTIONS += --with-jpeg
CONFIGURE_OPTIONS += --with-xpm
CONFIGURE_OPTIONS += --with-freetype
CONFIGURE_OPTIONS += --with-gmp
CONFIGURE_OPTIONS += --with-enchant
CONFIGURE_OPTIONS += --with-unixODBC
CONFIGURE_OPTIONS += --with-openssl-dir=$(OPENSSL_PREFIX)

# remove EXTRA_FLAGS to get the right ssl and crypto libs
# now with fix to cover all EXTRA_LDFLAGS conditions
COMPONENT_POST_CONFIGURE_ACTION= \
	(cd $(@D) ; \
        $(GSED) -i -e 's:^EXTRA_LDFLAGS = .*:EXTRA_LDFLAGS = -avoid-version -module:' -e 's:-L/usr/lib/$(MACH64) ::' -e 's:-R/usr/lib/$(MACH64) ::' Makefile )

# Installation Arguments
COMPONENT_INSTALL_ARGS += INSTALL_ROOT=$(PROTO_DIR)

# Pre-Install Actions
COMPONENT_PRE_INSTALL_ACTION += \
	  ( $(MKDIR) -p $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d ; \
	  echo "Creating fake modules.load and httpd.conf" ; \
	  echo "\# LoadModule foo_module libexec/mod_foo.so" >> $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d/modules.load ; \
	  echo "\# " >> $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d/modules.load ; \
	  echo "LoadModule foo_module libexec/mod_foo.so " >> $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d/modules.load ; \
          cp $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d/modules.load  $(PROTO_DIR)/$(AP_SYSCONFDIR)/httpd.conf \
)

# Environment Variables
CONFIGURE_ENV += EXTENSION_DIR=$(PHP_PREFIX)/extensions
CONFIGURE_ENV += ICU_CONFIG=/usr/bin/icu-config
CONFIGURE_ENV += PG_CONFIG=$(PG_BINDIR)/pg_config
CONFIGURE_ENV += PKG_CONFIG_PATH=$(OPENSSL_PREFIX)/lib/$(MACH64)/pkgconfig

COMPONENT_TEST_TARGETS = test

COMPONENT_TEST_ENV += NO_INTERACTION=yes

# Test results are unstable between runs but still useful for humans.
# test failures; keep going
COMPONENT_TEST_ARGS +=	-k -i
COMPONENT_TEST_TRANSFORMS += \
    '-e "/^make/d" ' \
    '-e "/^Time taken/d" ' \
    '-e "/^TEST RESULT SUMMARY$$/,\$$p" ' \
    '-e "/.*/d" '

# Manually added build dependencies
REQUIRED_PACKAGES += $(MYSQL_CLIENT_PKG)
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)
REQUIRED_PACKAGES += $(PG_SERVICE_PKG)
REQUIRED_PACKAGES += web/server/apache-24

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/libzip
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += library/unixodbc
REQUIRED_PACKAGES += library/uw-imap
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += text/aspell
REQUIRED_PACKAGES += text/oniguruma
REQUIRED_PACKAGES += text/tidy
REQUIRED_PACKAGES += web/curl
