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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		php
COMPONENT_VERSION=	5.4.26
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:ec3f902b5e8cbdd660e01e784b537f1210a12182d9bbd62164776075bc097eca
COMPONENT_ARCHIVE_URL=	http://uk3.php.net/get/$(COMPONENT_ARCHIVE)/from/this/mirror

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH= /usr/bin:/usr/gnu/bin:/usr/sbin

# Apache Paths
AP_PREFIX=/usr/apache2/2.4
AP_SYSCONFDIR=/etc/apache2/2.4

# PHP Paths
PHP_PREFIX=/usr/php/5.4
PHP_SYSCONFDIR=/etc/php/5.4
PHP_DATADIR=/var/php/5.4

CFLAGS = $(CC_BITS) -D_POSIX_PTHREAD_SEMANTICS

# Configure Options

CONFIGURE_OPTIONS      =	--prefix=$(PHP_PREFIX)
CONFIGURE_OPTIONS.32   =	--bindir=$(PHP_PREFIX)/bin
CONFIGURE_OPTIONS.64   =	--bindir=$(PHP_PREFIX)/bin/$(MACH64)
CONFIGURE_OPTIONS.32  +=	--sbindir=$(PHP_PREFIX)/bin
CONFIGURE_OPTIONS.64  +=	--sbindir=$(PHP_PREFIX)/bin/$(MACH64)
CONFIGURE_OPTIONS.32  +=	--libdir=$(PHP_PREFIX)/lib
CONFIGURE_OPTIONS.64  +=	--libdir=$(PHP_PREFIX)/lib/$(MACH64)
CONFIGURE_OPTIONS.32  +=	--libexecdir=$(PHP_PREFIX)/libexec
CONFIGURE_OPTIONS.64  +=	--libexecdir=$(PHP_PREFIX)/libexec/$(MACH64)
CONFIGURE_OPTIONS     +=	--includedir=$(PHP_PREFIX)/include
CONFIGURE_OPTIONS     +=	--sysconfdir=$(PHP_SYSCONFDIR)
CONFIGURE_OPTIONS     +=	--datadir=$(PHP_DATADIR)
CONFIGURE_OPTIONS     +=	--mandir=$(PHP_PREFIX)/share/man
CONFIGURE_OPTIONS     +=	--localstatedir=$(PHP_DATADIR)

# SAPI modules
CONFIGURE_OPTIONS.32  +=	--with-apxs2=$(AP_PREFIX)/bin/apxs
CONFIGURE_OPTIONS.64  +=	--with-apxs2=$(AP_PREFIX)/bin/$(MACH64)/apxs

CONFIGURE_OPTIONS.64  +=	--build=x86_64-pc-solaris$(SOLARIS_VERSION)

CONFIGURE_OPTIONS     +=	--with-config-file-path=$(PHP_SYSCONFDIR)
CONFIGURE_OPTIONS     +=	--with-config-file-scan-dir=$(PHP_SYSCONFDIR)/conf.d
CONFIGURE_OPTIONS     +=	--with-pear=$(PHP_PREFIX)/share/PEAR

CONFIGURE_OPTIONS     +=	--with-layout=PHP
CONFIGURE_OPTIONS     +=	--with-zend-vm=CALL

CONFIGURE_OPTIONS     +=	--with-cdb
CONFIGURE_OPTIONS     +=	--with-kerberos
CONFIGURE_OPTIONS     +=	--with-pcre-regex

# Disabled extensions & Options
CONFIGURE_OPTIONS     +=	--disable-static
CONFIGURE_OPTIONS     +=	--disable-dba
CONFIGURE_OPTIONS     +=	--disable-debug
CONFIGURE_OPTIONS     +=	--disable-libgcc
#CONFIGURE_OPTIONS     +=	--disable-inline-optimization
#CONFIGURE_OPTIONS     +=	--disable-libtool-lock
#CONFIGURE_OPTIONS     +=	--disable-rpath

CONFIGURE_OPTIONS     +=	--enable-dtrace
CONFIGURE_OPTIONS     +=	--without-dbm
CONFIGURE_OPTIONS     +=	--without-t1lib

CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))

# Installation Arguments
COMPONENT_INSTALL_ARGS  += INSTALL_ROOT=$(PROTO_DIR)

# Pre-Install Actions
COMPONENT_PRE_INSTALL_ACTION+= \
	  ( $(MKDIR) -p $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d ; \
	  echo "Creating fake modules-32.load, modules-64.load and httpd.conf" ; \
	  echo "\# LoadModule foo_module libexec/mod_foo.so" >> $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d/modules-32.load ; \
	  echo "\# " >> $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d/modules-32.load ; \
	  echo "LoadModule foo_module libexec/mod_foo.so " >> $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d/modules-32.load ; \
	  cp $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d/modules-32.load  $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d/modules-64.load ; \
          cp $(PROTO_DIR)/$(AP_SYSCONFDIR)/conf.d/modules-32.load  $(PROTO_DIR)/$(AP_SYSCONFDIR)/httpd.conf \
	  )

# Environment Variables
COMPONENT_BUILD_ENV+=	CC="$(CC) $(CC_BITS)" CXX="$(CXX)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"
CONFIGURE_ENV.32 +=     EXTENSION_DIR=$(PHP_PREFIX)/extensions
CONFIGURE_ENV.64 +=     EXTENSION_DIR=$(PHP_PREFIX)/extensions/$(MACH64)

COMPONENT_BUILD_TARGETS = libphp5.la
COMPONENT_INSTALL_TARGETS = install-sapi

build:		$(BUILD_32_and_64) 

install:	$(INSTALL_32_and_64)
