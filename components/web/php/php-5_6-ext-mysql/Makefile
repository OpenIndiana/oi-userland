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

# TODO: Revise structures below to utilize well the new common configure.mk
CONFIGURE_PROTO_DIRS:=no
CONFIGURE_DEFAULT_DIRS:=no
CONFIGURE_DEFAULT_EXTRA_DIRS:=no
CONFIGURE_DEFAULT_STATE_DIRS:=no

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		php
COMPONENT_VERSION=      5.6.27
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:16eb544498339d1d855292826e2e547ab01a31600141094959073e5e10e93ab5
COMPONENT_ARCHIVE_URL=	http://uk1.php.net/get/$(COMPONENT_ARCHIVE)/from/this/mirror

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PHP_PREFIX=/usr/php/5.6
PHP_SYSCONFDIR=/etc/php/5.6
PHP_DATADIR=/var/php/5.6

CONFIGURE_OPTIONS	=	--prefix=$(PHP_PREFIX)
CONFIGURE_OPTIONS.32	=	--bindir=$(PHP_PREFIX)/bin
CONFIGURE_OPTIONS.64	=	--bindir=$(PHP_PREFIX)/bin/$(MACH64)
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

CONFIGURE_OPTIONS.64  +=	--build=x86_64-pc-solaris2.10
CONFIGURE_OPTIONS.32  +=	--with-php-config=$(PHP_PREFIX)/bin/php-config
CONFIGURE_OPTIONS.64  +=	--with-php-config=$(PHP_PREFIX)/bin/$(MACH64)/php-config
CONFIGURE_OPTIONS     +=	--with-mysql=/usr/mariadb/5.5

CONFIGURE_OPTIONS     +=	$(CONFIGURE_OPTIONS.$(BITS))

LDFLAGS.32            +=	-L/usr/mariadb/5.5/lib -R/usr/mariadb/5.5/lib
LDFLAGS.64            +=	-L/usr/mariadb/5.5/lib/$(MACH64) -R/usr/mariadb/5.5/lib/$(MACH64)

CFLAGS		   	=	$(CC_BITS) -D_POSIX_PTHREAD_SEMANTICS
CFLAGS			+=	-I/usr/mariadb/5.5/include
CPPFLAGS 	        +=	-I/usr/mariadb/5.5/include
LDFLAGS			+=	$(LDFLAGS.$(BITS))

CONFIGURE_SCRIPT       =	$(@D)/configure

COMPONENT_PRE_CONFIGURE_ACTION	 =	cp -R $(SOURCE_DIR)/ext/mysql/* $(@D) ; cd $(@D) ; $(PHP_PREFIX)/bin/phpize
COMPONENT_POST_CONFIGURE_ACTION	 =	perl -p -i -e 's/MYSQL_SHARED_LIBADD = .*/MYSQL_SHARED_LIBADD = -lmysqlclient/g' $(@D)/Makefile
COMPONENT_INSTALL_ARGS		+=	INSTALL_ROOT=$(PROTO_DIR)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

REQUIRED_PACKAGES += database/mariadb-55/library
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/php-56/php-common
