#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2016 Sergey Avseyev
# Copyright (c) 2019 Alexander Pyhalov
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pecl-memcache
COMPONENT_VERSION=	4.0.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://pecl.php.net/package/memcache
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tgz
COMPONENT_ARCHIVE_HASH=	sha256:59cc60f6226e802575e8930eea977bf66aa3df7b47cecdb3a6e82b08fb729c78
COMPONENT_ARCHIVE_URL=	https://github.com/websupport-sk/pecl-memcache/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_SUMMARY=	php memcache extension
COMPONENT_FMRI=		web/php-73/extension/php-memcache
COMPONENT_LICENSE=	PHP3.01
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_CLASSIFICATION=	Development/PHP

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CLEAN_PATHS +=  package.xml

PHP_PREFIX=/usr/php/7.3
PHP_SYSCONFDIR=/etc/php/7.3
PHP_DATADIR=/var/php/7.3

# Configure Options
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

CONFIGURE_OPTIONS.64  +=        --build=x86_64-pc-solaris2.10
CONFIGURE_OPTIONS  +=   --with-php-config=$(PHP_PREFIX)/bin/php-config

CONFIGURE_OPTIONS     +=	$(CONFIGURE_OPTIONS.$(BITS))

CFLAGS                +=	-I/usr/include -I$(PHP_PREFIX)/include
CPPFLAGS              +=	$(CFLAGS)
LDFLAGS.32            +=	-L$(PHP_PREFIX)/lib -R$(PHP_PREFIX)/lib
LDFLAGS.64            +=	-L$(PHP_PREFIX)/lib/$(MACH64) -R$(PHP_PREFIX)/lib/$(MACH64)
LDFLAGS               +=	$(LDFLAGS.$(BITS))

CONFIGURE_OPTIONS     +=        CC="$(CC)" CXX="$(CXX)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"
CONFIGURE_ENV         +=	CC="$(CC)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"
CONFIGURE_SCRIPT       =	$(@D)/configure

COMPONENT_PRE_CONFIGURE_ACTION	 =	cp -R $(SOURCE_DIR)/* $(@D) ; cd $(@D) ; $(PHP_PREFIX)/bin/phpize
COMPONENT_INSTALL_ARGS		+=	INSTALL_ROOT=$(PROTO_DIR)

build:		$(BUILD_64)

install:	$(INSTALL_64)

REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/php-73/php-common
