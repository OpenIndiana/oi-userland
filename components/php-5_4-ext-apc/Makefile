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
# Copyright 2013 EveryCity Ltd. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		APC
COMPONENT_FMRI=		web/php-54/extension/php-apc
COMPONENT_VERSION=	3.1.13
COMPONENT_LICENSE=	PHP3.01
COMPONENT_PROJECT_URL=	http://pecl.php.net/package/APC
COMPONENT_SUMMARY=	APC is a free, open, and robust framework for caching and optimizing PHP intermediate code
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	sha256:5ef8ba07729e72946e95951672a5378bed98cb5a294e79bf0f0a97ac62829abd
COMPONENT_ARCHIVE_URL=	http://pecl.php.net/get/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CLEAN_PATHS +=	package.xml

# PHP Paths
PHP_PREFIX=/usr/php/5.4
PHP_SYSCONFDIR=/etc/php/5.4
PHP_DATADIR=/var/php/5.4

CONFIGURE_OPTIONS      =	--prefix=$(PHP_PREFIX)
CONFIGURE_OPTIONS.32  +=	--bindir=$(PHP_PREFIX)/bin
CONFIGURE_OPTIONS.64  +=	--bindir=$(PHP_PREFIX)/bin/$(MACH64)
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

CONFIGURE_OPTIONS     +=	$(CONFIGURE_OPTIONS.$(BITS))

CFLAGS                +=	-I$(PHP_PREFIX)/include $(CC_BITS)
CPPFLAGS              +=	$(CFLAGS)
LDFLAGS.32            +=	-L$(PHP_PREFIX)/lib -R$(PHP_PREFIX)/lib
LDFLAGS.64            +=	-L$(PHP_PREFIX)/lib/$(MACH64) -R$(PHP_PREFIX)/lib/$(MACH64)

CONFIGURE_OPTIONS     +=	CC="$(CC)" CXX="$(CXX)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"

CONFIGURE_SCRIPT       =	$(@D)/configure

COMPONENT_PRE_CONFIGURE_ACTION	 =	cp -R $(SOURCE_DIR)/* $(@D) ; cd $(@D) ; $(PHP_PREFIX)/bin/phpize
COMPONENT_INSTALL_ARGS		+=	INSTALL_ROOT=$(PROTO_DIR)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

