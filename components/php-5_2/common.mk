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
#

PHP_REL=		5.2

TOP_DIR=/usr/php/$(PHP_REL)
CONF_DIR=/etc/php/$(PHP_REL)
ZTS_MODULES_DIR=$(TOP_DIR)/zts-modules

APACHE_VERSION_DIR=2.2
APACHE_DIR_PREFIX=apache2/$(APACHE_VERSION_DIR)
APACHE_USR_PREFIX=/usr/$(APACHE_DIR_PREFIX)
APACHE_VAR_PREFIX=/var/$(APACHE_DIR_PREFIX)
APACHE_ETC_PREFIX=/etc/$(APACHE_DIR_PREFIX)
APACHE2_SAMPLES_CONFDIR=$(APACHE_ETC_PREFIX)/samples-conf.d
APACHE2_CONFDIR=$(APACHE_ETC_PREFIX)/conf.d
APACHE2_PHP=$(APACHE2_CONFDIR)/php
APACHE2_EXTDIR=$(APACHE_USR_PREFIX)/libexec
PHP_ROOT=/usr/php/$(PHP_REL)
PHP_BIN=$(PHP_ROOT)/bin
PHP_LIB=$(PHP_ROOT)/lib
PHP_ROOT_EXT=$(PHP_ROOT)/modules
PHP_ROOT_ZTS_EXT=$(PHP_ROOT)/zts-modules
EXTDIR=$(TOP_DIR)/modules
CONFDIR=/etc/php/$(PHP_REL)
MODULES_CONFDIR=$(CONFDIR)/conf.d
NSAPI_CONFDIR=/etc/php/$(PHP_REL)/nsapi
ZTS_MODULES_CONFDIR=$(CONFDIR)/zts-conf.d
COPYRIGHT_TMPL=$(COMPONENT_DIR)/../Solaris/copyright.tmpl
DOCDIR=$(PHP_ROOT)/doc
SCRIPTS_DIR=$(PHP_ROOT)/samples/scripts

IMAP_DIR = $(COMPONENT_DIR)/../imap/build/$(MACH32)
IMAP_CLIENT_DIR = $(IMAP_DIR)/c-client
MODULES_DIR = $(TOP_DIR)/modules
MODULES_CONF_DIR=$(CONF_DIR)/conf.d
MYSQL_DIR = /usr/mysql/5.1
MYSQL_LIBDIR=/usr/mysql/5.1/lib/mysql
PHP_SAPI_BUILD = $(COMPONENT_DIR)/../php-sapi/build/$(MACH32)
PEAR_DIR=/var/php/$(PHP_REL)/pear


COMMON_CONFIG_OPTIONS= \
	--bindir=$(TOP_DIR)/bin \
	--datadir=$(TOP_DIR)/share \
	--disable-dbase \
	--disable-debug \
	--disable-dmalloc  \
	--disable-inline-optimization \
	--disable-libgcc \
	--disable-libtool-lock \
	--disable-rpath \
	--disable-static \
	--enable-bcmath \
	--enable-calendar \
	--enable-ctype \
	--enable-cli \
	--enable-dom \
	--enable-dtrace \
	--enable-exif \
	--enable-flatfile \
	--enable-filter \
	--enable-gd-jis-conv \
	--enable-gd-native-ttf \
	--enable-hash \
	--enable-inifile \
	--enable-ipv6 \
	--enable-json \
	--enable-magic-quotes \
	--enable-mbregex \
	--enable-mbstring \
	--enable-mod-charset \
	--enable-pcntl \
	--enable-posix \
	--enable-reflection \
	--with-libxml-dir=/usr \
	--enable-libxml \
	--enable-sqlite-utf8 \
	--enable-session \
	--enable-shared \
	--enable-shmop \
	--enable-short-tags \
	--enable-simplexml \
	--enable-soap \
	--enable-sockets \
	--enable-spl \
	--enable-sysvmsg \
	--enable-sysvsem \
	--enable-sysvshm \
	--enable-tokenizer \
	--enable-xml \
	--enable-xmlreader \
	--enable-xmlwriter \
	--enable-zend-multibyte \
	--enable-zip \
	--exec-prefix=$(TOP_DIR) \
	--includedir=$(TOP_DIR)/include \
	--libdir=$(TOP_DIR)/lib \
	--libexecdir=$(TOP_DIR)/modules \
	--mandir=$(TOP_DIR)/man \
	--oldincludedir=$(TOP_DIR)/share \
	--prefix=$(TOP_DIR) \
	--sbindir=$(TOP_DIR)/sbin \
	--sysconfdir=$(CONF_DIR) \
	--with-cdb \
	--with-exec-dir=$(TOP_DIR)/bin \
	--with-freetype-dir=/usr/sfw \
	--with-jpeg-dir=/usr \
	--with-kerberos \
	--with-layout=PHP \
	--with-mcrypt=shared,/usr \
	--with-pcre-dir=/usr \
	--with-pcre-regex \
	--with-png-dir=/usr \
	--with-xmlrpc \
	--with-xpm-dir=/usr/X11 \
	--with-xsl \
	--with-zlib \
	--with-zend-vm=CALL \
	--without-dbm \
	--without-t1lib


studio_C99MODE = $(studio_99_ENABLE)
studio_cplusplus_C99MODE = $(studio_cplusplus_C99_ENABLE)
CPPFLAGS += -D_POSIX_PTHREAD_SEMANTICS
CPPFLAGS += $(CPP_LARGEFILES)
CPPFLAGS += -I../CPPFLAGSTEST
LIBS = -lsocket -lnsl -ldl -lposix4
LD = $(CXX) $(studio_NORUNPATH)
LDFLAGS += -L$(MYSQL_LIBDIR) -lrt -L$(IMAP_CLIENT_DIR)

CONFIGURE_OPTIONS  +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS  +=	LD="$(LD)"
CONFIGURE_OPTIONS  +=	LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS  +=	PATH="$(PATH):/usr/sbin"

CONF_ENVLINE += \
	LIBS="$(LIBS)" \
	EXTENSION_DIR=$(MODULES_DIR) \
	PHP_PEAR_CACHE_DIR=/var/tmp/pear/cache \
	PHP_PEAR_DOWNLOAD_DIR=/var/tmp/pear/cache \
	PHP_PEAR_EXTENSION_DIR=/var/php/$(PHP_REL)/modules \
	PHP_PEAR_INSTALL_DIR=/var/php/$(PHP_REL)/pear \
	PHP_PEAR_SIG_BIN=/usr/gnu/bin/gpg \
	DESTDIR=$(PROTO_DIR) \
	INSTALL_ROOT=$(PROTO_DIR) \
	INSTALL=$(INSTALL)

PHP_ZTS_CFLAGS=-mt -D_REENTRANT
ZTS_MODULES_CONF_DIR=$(CONF_DIR)/zts-conf.d


ZTS_CONF_ENVLINE= \
	CC=$(CC) \
	CXX=$(CXX) \
	CPPFLAGS="-I../CPPFLAGSTEST -D_POSIX_PTHREAD_SEMANTICS" \
	CFLAGS="$(CFLAGS) $(PHP_ZTS_CFLAGS)" \
	LDFLAGS="-L$(MYSQL_LIBDIR) -lrt" \
	LIBS="$(LIBS)" \
	EXTENSION_DIR=$(ZTS_MODULES_DIR) \
	DESTDIR=$(PROTO_DIR) \
	INSTALL_ROOT=$(PROTO_DIR) \
	INSTALL=$(INSTALL)

ENVLINE= \
        $(CONF_ENVLINE)

ZTS_ENVLINE= \
	$(ZTS_CONF_ENVLINE)

COMPONENT_BUILD_ENV += PATH="$(PATH):/usr/sbin"
COMPONENT_INSTALL_ENV += $(CONFIGURE_ENV)

COMPONENT_TEST_ENV += $(CONFIGURE_ENV)
COMPONENT_TEST_TARGETS = test
# Turns off question at the end of the test run.
COMPONENT_TEST_ENV += NO_INTERACTION=1

# We provide an .ini file for some extensions.
# Extensions without .ini's get handled below.
FIX_CONFIG_FILES = ( \
	$(MKDIR) $(COMPONENT_DIR)/tmp; \
	cd $(COMPONENT_DIR)/tmp; \
	$(MKDIR) $(PROTO_DIR)/$(MODULES_CONFDIR); \
	$(MKDIR) $(PROTO_DIR)/$(ZTS_MODULES_CONFDIR); \
	for conffile in ../config/*.ini; do \
		ext=$${conffile\#\#*/}; \
		$(INSTALL) -m 644 $${conffile} \
			$(PROTO_DIR)/$(MODULES_CONFDIR)/$${ext}; \
		$(GSED) -e "s@zend_extension=$(PHP_ROOT_EXT)@zend_extension=$(PHP_ROOT_ZTS_EXT)@" < $${conffile} > tmp; \
		$(INSTALL) -m 644 tmp \
			$(PROTO_DIR)/$(ZTS_MODULES_CONFDIR)/$${ext}; \
	done; \
	)


# Prepare configuration files for each extension
# By default, disable following 3rd party extensions:
# xdebug suhosin
FIX_CONFIG_FILES_2 = ( \
	$(MKDIR) $(COMPONENT_DIR)/tmp; \
	cd $(COMPONENT_DIR)/tmp; \
	$(MKDIR) $(PROTO_DIR)/$(MODULES_CONFDIR); \
	$(MKDIR) $(PROTO_DIR)/$(ZTS_MODULES_CONFDIR); \
	for module in $(PROTO_DIR)/$(EXTDIR)/*.so; do \
		module=$${module%.so}; \
		ext=$${module\#\#*/}; \
		echo "extension=$${ext}.so" > $${ext}.ini; \
		$(INSTALL) -m 644 $${ext}.ini \
			$(PROTO_DIR)/$(MODULES_CONFDIR)/$${ext}.ini; \
		$(INSTALL) -m 644 $${ext}.ini \
			$(PROTO_DIR)/$(ZTS_MODULES_CONFDIR)/$${ext}.ini; \
	done; \
	)
