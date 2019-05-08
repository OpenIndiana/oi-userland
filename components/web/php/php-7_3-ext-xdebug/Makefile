# Copyright 2011 EveryCity Ltd. All rights reserved.
#
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

COMPONENT_NAME=		xdebug
COMPONENT_VERSION=	2.7.2
COMPONENT_PROJECT_URL=	http://pecl.php.net/package/xdebug
COMPONENT_SUMMARY=	Provides functions for debugging your PHP script
COMPONENT_FMRI=		web/php-73/extension/php-xdebug
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	sha256:b0f3283aa185c23fcd0137c3aaa58554d330995ef7a3421e983e8d018b05a4a6
COMPONENT_ARCHIVE_URL=	http://pecl.php.net/get/$(COMPONENT_SRC).tgz
COMPONENT_LICENSE=	PHP3.0
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

CONFIGURE_OPTIONS.64  +=	--build=x86_64-pc-solaris2.10
CONFIGURE_OPTIONS  +=	--with-php-config=$(PHP_PREFIX)/bin/php-config

CONFIGURE_OPTIONS     +=	$(CONFIGURE_OPTIONS.$(BITS))
CONFIGURE_OPTIONS     +=        CPPFLAGS="$(CPPFLAGS)"

CFLAGS                +=	-I/usr/include -I$(PHP_PREFIX)/include
CPPFLAGS              +=	$(CFLAGS) -DNAME_MAX=1024
LDFLAGS.32            +=	-L$(PHP_PREFIX)/lib -R$(PHP_PREFIX)/lib
LDFLAGS.64            +=	-L$(PHP_PREFIX)/lib/$(MACH64) -R$(PHP_PREFIX)/lib/$(MACH64)

CONFIGURE_SCRIPT       =	$(@D)/configure

COMPONENT_PRE_CONFIGURE_ACTION	 =	cp -R $(SOURCE_DIR)/* $(@D) ; cd $(@D) ; $(PHP_PREFIX)/bin/phpize
COMPONENT_INSTALL_ARGS		+=	INSTALL_ROOT=$(PROTO_DIR)

build:		$(BUILD_64)

install:	$(INSTALL_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/php-73/php-common
