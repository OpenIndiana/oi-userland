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
#
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		php
COMPONENT_MJR_VERSION=	7.3
COMPONENT_MNR_VERSION=	8
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:f6046b2ae625d8c04310bda0737ac660dc5563a8e04e8a46c1ee24ea414ad5a5
COMPONENT_ARCHIVE_URL=	http://uk1.php.net/get/$(COMPONENT_ARCHIVE)/from/this/mirror
COMPONENT_SIG_URL=	http://uk1.php.net/get/$(COMPONENT_ARCHIVE).asc/from/this/mirror
COMPONENT_LICENSE=	PHP License
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

# Apache Paths
AP_PREFIX=/usr/apache2/2.4
AP_SYSCONFDIR=/etc/apache2/2.4

# PHP Paths
PHP_PREFIX=/usr/php/$(COMPONENT_MJR_VERSION)
PHP_SYSCONFDIR=/etc/php/$(COMPONENT_MJR_VERSION)
PHP_DATADIR=/var/php/$(COMPONENT_MJR_VERSION)

CFLAGS			= $(CC_BITS) -D_POSIX_PTHREAD_SEMANTICS
CPPFLAGS		+= $(CPP_XPG6MODE)
CPPFLAGS		+= -I/usr/include/openldap
CPPFLAGS		+=      -I$(MYSQL_INCDIR)
CFLAGS			+=	-I$(MYSQL_INCDIR)
LDFLAGS		+=	-L$(MYSQL_LIBDIR) -R$(MYSQL_LIBDIR)

# build with the system default libjpeg
CFLAGS		+=	$(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS	+=	$(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
CPPFLAGS	+=	$(JPEG_CPPFLAGS)
LDFLAGS		+=	$(JPEG_LDFLAGS)

COMPONENT_PREP_ACTION =        ( cd $(@D) && autoconf )

# Configure Options
CONFIGURE_OPTIONS  =	--prefix=$(PHP_PREFIX)
CONFIGURE_OPTIONS  +=	--bindir=$(PHP_PREFIX)/bin
CONFIGURE_OPTIONS  +=	--sbindir=$(PHP_PREFIX)/bin
CONFIGURE_OPTIONS  +=	--libdir=$(PHP_PREFIX)/lib/$(MACH64)
CONFIGURE_OPTIONS  +=	--libexecdir=$(PHP_PREFIX)/libexec
CONFIGURE_OPTIONS  +=	--includedir=$(PHP_PREFIX)/include
CONFIGURE_OPTIONS  +=	--sysconfdir=$(PHP_SYSCONFDIR)
CONFIGURE_OPTIONS  +=	--datadir=$(PHP_DATADIR)
CONFIGURE_OPTIONS  +=	--mandir=$(PHP_PREFIX)/share/man
CONFIGURE_OPTIONS  +=	--localstatedir=$(PHP_DATADIR)
CONFIGURE_OPTIONS  +=	--enable-maintainer-zts

# SAPI modules
CONFIGURE_OPTIONS  +=	--with-apxs2=$(AP_PREFIX)/bin/apxs
CONFIGURE_OPTIONS  +=   --enable-fpm

CONFIGURE_OPTIONS.64  +=	--build=x86_64-pc-solaris$(SOLARIS_VERSION)

CONFIGURE_OPTIONS  +=	--with-config-file-path=$(PHP_SYSCONFDIR)
CONFIGURE_OPTIONS  +=	--with-config-file-scan-dir=$(PHP_SYSCONFDIR)/conf.d
CONFIGURE_OPTIONS  +=	--with-pear=$(PHP_PREFIX)/share/PEAR

CONFIGURE_OPTIONS  +=	--with-layout=PHP

CONFIGURE_OPTIONS  +=	--with-cdb
CONFIGURE_OPTIONS  +=	--with-kerberos
CONFIGURE_OPTIONS  +=	--with-pcre-regex
CONFIGURE_OPTIONS  +=	--with-readline
CONFIGURE_OPTIONS   +=	--enable-dtrace

# So far we don't ship libzip, use bundled one
CONFIGURE_OPTIONS  +=   --with-libzip=no

# Shared Extensions
CONFIGURE_OPTIONS   +=	--with-gettext=shared
CONFIGURE_OPTIONS   +=	--with-xmlrpc=shared
CONFIGURE_OPTIONS   +=	--with-gd=shared
CONFIGURE_OPTIONS   +=	--with-zlib=shared
CONFIGURE_OPTIONS   +=	--with-openssl=shared
CONFIGURE_OPTIONS   +=	--with-pdo-sqlite=shared
CONFIGURE_OPTIONS   +=	--with-ldap=shared
CONFIGURE_OPTIONS   +=	--with-bz2=shared
CONFIGURE_OPTIONS   +=	--with-iconv=shared
CONFIGURE_OPTIONS   +=	--with-tidy=shared
CONFIGURE_OPTIONS   +=	--with-mhash=shared
CONFIGURE_OPTIONS   +=	--with-xsl=shared
CONFIGURE_OPTIONS   +=	--with-curl=shared
CONFIGURE_OPTIONS   +=	--with-pspell=shared
CONFIGURE_OPTIONS   +=	--with-imap=shared
CONFIGURE_OPTIONS   +=	--with-imap-ssl

# Extensions, dependent on other packages

CONFIGURE_OPTIONS  +=	--with-mysqli=shared,$(MYSQL_BINDIR)/mysql_config
CONFIGURE_OPTIONS  +=	--with-pdo-mysql=shared,$(MYSQL_BINDIR)/mysql_config
CONFIGURE_OPTIONS  +=	--with-pgsql=shared,$(PG_BINDIR)
CONFIGURE_OPTIONS  +=	--with-pdo-pgsql=shared,$(PG_BINDIR)

# Enabled Extensions
#CONFIGURE_OPTIONS     +=	--with-libxml-dir=$(ECPREFIX)
#CONFIGURE_OPTIONS     +=	--with-freetype-dir=$(ECPREFIX)
CONFIGURE_OPTIONS   +=	--with-jpeg-dir=/usr
#CONFIGURE_OPTIONS     +=	--with-png-dir=$(ECPREFIX)
#CONFIGURE_OPTIONS     +=	--with-zlib-dir=$(ECPREFIX)
#CONFIGURE_OPTIONS     +=	--with-xpm-dir=$(ECPREFIX)
#CONFIGURE_OPTIONS     +=	--with-libexpat-dir=$(ECPREFIX)
#CONFIGURE_OPTIONS     +=	--with-openssl-dir=$(ECPREFIX)

# Disabled extensions & Options
CONFIGURE_OPTIONS   +=	--disable-static
CONFIGURE_OPTIONS   +=	--disable-dba
CONFIGURE_OPTIONS   +=	--disable-debug
CONFIGURE_OPTIONS   +=	--disable-libgcc
CONFIGURE_OPTIONS   +=	--without-dbm

# Enabled extensions
CONFIGURE_OPTIONS   +=	--enable-cli
CONFIGURE_OPTIONS   +=	--enable-cgi
CONFIGURE_OPTIONS   +=	--enable-shared
CONFIGURE_OPTIONS   +=	--enable-filter
CONFIGURE_OPTIONS   +=	--enable-gd-jis-conv
CONFIGURE_OPTIONS   +=	--enable-short-tags
CONFIGURE_OPTIONS   +=	--enable-pcntl
CONFIGURE_OPTIONS   +=	--enable-shmop
CONFIGURE_OPTIONS   +=	--enable-sysvmsg
CONFIGURE_OPTIONS   +=	--enable-sysvsem
CONFIGURE_OPTIONS   +=	--enable-sysvshm
CONFIGURE_OPTIONS   +=	--enable-simplexml
CONFIGURE_OPTIONS   +=	--enable-hash
CONFIGURE_OPTIONS   +=	--enable-session
CONFIGURE_OPTIONS   +=	--enable-opcache

# Shared Extensions
CONFIGURE_OPTIONS   +=	--enable-bcmath=shared
CONFIGURE_OPTIONS   +=	--enable-json=shared
CONFIGURE_OPTIONS   +=	--enable-libxml=shared
CONFIGURE_OPTIONS   +=	--enable-ctype=shared
CONFIGURE_OPTIONS   +=	--enable-calendar=shared
CONFIGURE_OPTIONS   +=	--enable-tokenizer=shared
CONFIGURE_OPTIONS   +=	--enable-exif=shared
CONFIGURE_OPTIONS   +=	--enable-dom=shared
CONFIGURE_OPTIONS   +=	--enable-ftp=shared
CONFIGURE_OPTIONS   +=	--enable-intl=shared
CONFIGURE_OPTIONS   +=	--enable-pdo=shared
CONFIGURE_OPTIONS   +=	--enable-mbstring=shared
CONFIGURE_OPTIONS   +=	--enable-xmlreader=shared
CONFIGURE_OPTIONS   +=	--enable-xmlwriter=shared
CONFIGURE_OPTIONS   +=	--enable-soap=shared
CONFIGURE_OPTIONS   +=	--enable-sockets=shared
CONFIGURE_OPTIONS   +=	--enable-wddx=shared
CONFIGURE_OPTIONS   +=	--enable-zip=shared

CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))

# Installation Arguments
COMPONENT_INSTALL_ARGS  += INSTALL_ROOT=$(PROTO_DIR)

# Pre-Install Actions
COMPONENT_PRE_INSTALL_ACTION+= \
	  ( $(MKDIR) -p $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d ; \
	  echo "Creating fake modules.load and httpd.conf" ; \
	  echo "\# LoadModule foo_module libexec/mod_foo.so" >> $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d/modules.load ; \
	  echo "\# " >> $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d/modules.load ; \
	  echo "LoadModule foo_module libexec/mod_foo.so " >> $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d/modules.load ; \
          cp $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d/modules.load  $(PROTO_DIR)/$(AP_SYSCONFDIR)/httpd.conf \
)

# Environment Variables
COMPONENT_BUILD_ENV+=	CC="$(CC) $(CC_BITS)" CXX="$(CXX)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"
CONFIGURE_ENV +=     EXTENSION_DIR=$(PHP_PREFIX)/extensions
CONFIGURE_ENV.64 +=     ICU_CONFIG=/usr/bin/amd64/icu-config
CONFIGURE_ENV +=	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV +=	PG_CONFIG=$(PG_BINDIR)/pg_config

# sapi/fpm/tests/002.phpt leaves php-fpm running
COMPONENT_PRE_TEST_ACTION += (pkill -u `id -u` php-fpm; exit 0);

COMPONENT_TEST_TARGETS = test

COMPONENT_TEST_ENV += NO_INTERACTION=yes

# Test results are unstable between runs but still useful for humans.
# test failures; keep going
COMPONENT_TEST_ARGS += -k -i
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(BITS).master
COMPONENT_TEST_TRANSFORMS += \
    '-e "/^make/d" ' \
    '-e "/^Time taken/d" ' \
    '-e "/^TEST RESULT SUMMARY$$/,\$$p" ' \
    '-e "/.*/d" '

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:	$(TEST_64)

# Build dependencies
REQUIRED_PACKAGES += web/server/apache-24
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += database/postgres-94/developer

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += database/mariadb-101/library
REQUIRED_PACKAGES += database/postgres-94/library
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/uw-imap
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/aspell
REQUIRED_PACKAGES += text/tidy
REQUIRED_PACKAGES += web/curl
