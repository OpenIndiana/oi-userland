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
COMPONENT_VERSION=	5.6.33
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:9004995fdf55f111cd9020e8b8aff975df3d8d4191776c601a46988c375f3553
COMPONENT_ARCHIVE_URL=	http://uk1.php.net/get/$(COMPONENT_ARCHIVE)/from/this/mirror

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

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
CONFIGURE_OPTIONS     +=	--with-pdo-mysql=$(MYSQL_HOME)

CONFIGURE_OPTIONS     +=	$(CONFIGURE_OPTIONS.$(BITS))

CFLAGS                  =       $(CC_BITS) -D_POSIX_PTHREAD_SEMANTICS
CFLAGS                  +=      -I$(MYSQL_INCDIR)
CPPFLAGS                +=      -I$(MYSQL_INCDIR)
LDFLAGS                 +=      -L$(MYSQL_LIBDIR) -R$(MYSQL_LIBDIR)

CONFIGURE_ENV         +=	PDO_MYSQL_CONFIG=$(MYSQL_CONFIG)

CONFIGURE_SCRIPT       =	$(@D)/configure

COMPONENT_PRE_CONFIGURE_ACTION	=	cp -R $(SOURCE_DIR)/ext/pdo_mysql/* $(@D) ; cd $(@D) ; $(PHP_PREFIX)/bin/phpize
COMPONENT_POST_CONFIGURE_ACTION	=	perl -p -i -e 's/PDO_MYSQL_SHARED_LIBADD = .*/PDO_MYSQL_SHARED_LIBADD = -lmysqlclient -lthread -lsocket -lz -lnsl -lm -lrt/g' $(@D)/Makefile
COMPONENT_INSTALL_ARGS		+=	INSTALL_ROOT=$(PROTO_DIR)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += database/mariadb-101/library
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/php-56/php-common
