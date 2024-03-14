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
# Copyright (c) 2016 Sergey Avseyev
# Copyright (c) 2019 Alexander Pyhalov
# Copyright (c) 2022 Friedrich Kink
#

USE_OPENSSL11=  yes
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		php-8.1-ext-memcached
COMPONENT_REAL_NAME=	memcached
COMPONENT_VERSION=	3.1.5
COMPONENT_REVISION=	1
COMPONENT_FMRI=		web/php-81/extension/php-memcached
COMPONENT_SUMMARY=	PHP extension for interfacing with memcached via libmemcached library
COMPONENT_PROJECT_URL=	https://pecl.php.net/package/$(COMPONENT_REAL_NAME)
COMPONENT_SRC=		$(COMPONENT_REAL_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tgz
COMPONENT_ARCHIVE_HASH=	sha256:b288e45f839593e16c4d8508b241de51a86df4f7322153e6becb9e1c819021fd
COMPONENT_ARCHIVE_URL=	https://pecl.php.net/get/$(COMPONENT_SRC).tgz
COMPONENT_SUMMARY=	PHP extension for interfacing with memcached via libmemcached library
COMPONENT_LICENSE=	PHP3.01
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_CLASSIFICATION=	Development/PHP

TEST_TARGET	   =	$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CLEAN_PATHS +=  package.xml

PHP_PREFIX=/usr/php/8.1
PHP_SYSCONFDIR=/etc/php/8.1
PHP_DATADIR=/var/php/8.1

COMPONENT_PRE_CONFIGURE_ACTION	=	cp -R $(SOURCE_DIR)/* $(@D) ; cd $(@D) ; $(PHP_PREFIX)/bin/phpize
CONFIGURE_SCRIPT		=	$(@D)/configure
COMPONENT_INSTALL_ARGS		+=	INSTALL_ROOT=$(PROTO_DIR)

CONFIGURE_OPTIONS  =    --prefix=$(PHP_PREFIX)
CONFIGURE_OPTIONS  +=   --bindir=$(PHP_PREFIX)/bin
CONFIGURE_OPTIONS  +=   --sbindir=$(PHP_PREFIX)/bin
CONFIGURE_OPTIONS  +=   --libdir=$(PHP_PREFIX)/lib/$(MACH64)
CONFIGURE_OPTIONS  +=   --libexecdir=$(PHP_PREFIX)/libexec
CONFIGURE_OPTIONS  +=   --includedir=$(PHP_PREFIX)/include
CONFIGURE_OPTIONS  +=   --sysconfdir=$(PHP_SYSCONFDIR)
CONFIGURE_OPTIONS  +=   --datadir=$(PHP_DATADIR)
CONFIGURE_OPTIONS  +=   --mandir=$(PHP_PREFIX)/share/man
CONFIGURE_OPTIONS  +=   --localstatedir=$(PHP_DATADIR)
CONFIGURE_OPTIONS  +=	--disable-memcached-sasl

ifeq ($(strip $(MACH)),i386)
CONFIGURE_OPTIONS  +=	--build=x86_64-pc-solaris$(SOLARIS_VERSION)
else
CONFIGURE_OPTIONS.64+=	--build=sparcv9-sun-solaris$(SOLARIS_VERSION)
endif

CONFIGURE_OPTIONS  +=	--with-php-config=$(PHP_PREFIX)/bin/php-config

CFLAGS             +=	-I/usr/include -I$(PHP_PREFIX)/include
CPPFLAGS           +=	$(CFLAGS)
LDFLAGS            +=	-L$(PHP_PREFIX)/lib/$(MACH64) -R$(PHP_PREFIX)/lib/$(MACH64)

# manually added dependencies
REQUIRED_PACKAGES += web/php-81/php-common
REQUIRED_PACKAGES += web/php-81/extension/php-memcache

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libmemcached
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
