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
# Copyright (c) 2023 Friedrich Kink
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xdebug
COMPONENT_VERSION=	3.3.2
COMPONENT_PROJECT_URL=	https://pecl.php.net/package/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	Xdebug is a debugging and productivity extension for PHP
COMPONENT_FMRI=		web/php-82/extension/php-xdebug
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	sha256:15545b8311bedb5e7df08fd90d6653d9bf33629791e8119e70350475df932c55
COMPONENT_ARCHIVE_URL=	https://pecl.php.net/get/$(COMPONENT_SRC).tgz
COMPONENT_LICENSE=	BSD style
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_CLASSIFICATION=	Development/PHP

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CLEAN_PATHS +=  package.xml

PHP_PREFIX= /usr/php/8.2
PHP_SYSCONFDIR= /etc/php/8.2
PHP_DATADIR= /var/php/8.2

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

ifeq ($(strip $(MACH)),i386)
CONFIGURE_OPTIONS  +=	--build=x86_64-pc-solaris2.10
else
CONFIGURE_OPTIONS  +=	--build=sparcv9-sun-solaris$(SOLARIS_VERSION)
endif
CONFIGURE_OPTIONS  +=	--with-php-config=$(PHP_PREFIX)/bin/php-config
CONFIGURE_OPTIONS  +=   CPPFLAGS="$(CPPFLAGS)"

CFLAGS             +=	-I$(PHP_PREFIX)/include
CPPFLAGS           +=	$(CFLAGS) -DNAME_MAX=1024
LDFLAGS            +=	-L$(PHP_PREFIX)/lib/$(MACH64) -R$(PHP_PREFIX)/lib/$(MACH64)

CONFIGURE_SCRIPT    =	$(@D)/configure

COMPONENT_PRE_CONFIGURE_ACTION	 =	cp -R $(SOURCE_DIR)/* $(@D) ; cd $(@D) ; $(PHP_PREFIX)/bin/phpize
COMPONENT_INSTALL_ARGS		+=	INSTALL_ROOT=$(PROTO_DIR)

# manually added dependencies
REQUIRED_PACKAGES += web/php-82/php-common

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
