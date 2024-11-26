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
# Copyright (c) 2019 Alexander Pyhalov
# Copyright (c) 2024 Friedrich Kink
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		php-8.3-ext-mongodb
COMPONENT_VERSION=	1.20.0
COMPONENT_SUMMARY=	MongoDB driver for PHP
COMPONENT_PROJECT_URL=	https://pecl.php.net/package/mongodb
COMPONENT_SRC=		mongodb-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tgz
COMPONENT_ARCHIVE_HASH=	sha256:01e87973fe7e54aac52054ec4a99cdd439ed5c01f7e5b8ea0a57031850d8e75a
COMPONENT_ARCHIVE_URL=	https://pecl.php.net/get/$(COMPONENT_SRC).tgz
COMPONENT_FMRI=		web/php-83/extension/php-mongodb
COMPONENT_CLASSIFICATION=	Development/PHP
COMPONENT_LICENSE=	Apache v2.0
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_TARGETS = test

COMPONENT_TEST_ENV += NO_INTERACTION=yes

COMPONENT_TEST_TRANSFORMS += \
    '-e "/^make/d" ' \
    '-e "/^Time taken/d" ' \
    '-e "/^TEST RESULT SUMMARY$$/,\$$p" ' \
    '-e "/.*/d" '

CLEAN_PATHS +=  package.xml package2.xml

PHP_PREFIX=/usr/php/8.3
PHP_SYSCONFDIR=/etc/php/8.3
PHP_DATADIR=/var/php/8.3

# Configure Options
CONFIGURE_OPTIONS  +=   --prefix=$(PHP_PREFIX)
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
CONFIGURE_OPTIONS  +=	--build=x86_64-pc-solaris$(SOLARIS_VERSION)
else
CONFIGURE_OPTIONS  +=	--build=sparcv9-sun-solaris$(SOLARIS_VERSION)
endif

CONFIGURE_OPTIONS  +=	--with-php-config=$(PHP_PREFIX)/bin/php-config

CFLAGS             +=	-I$(PHP_PREFIX)/include -I/usr/include/pcre -D__EXTENSIONS__ -D__SOLARIS__
CPPFLAG            +=	$(CFLAGS)
LDFLAGS            +=	-L$(PHP_PREFIX)/lib -R$(PHP_PREFIX)/lib

CONFIGURE_SCRIPT   =	$(@D)/configure

COMPONENT_PRE_CONFIGURE_ACTION	 =	cp -R $(SOURCE_DIR)/* $(@D) ; cd $(@D) ; $(PHP_PREFIX)/bin/phpize
COMPONENT_INSTALL_ARGS		+=	INSTALL_ROOT=$(PROTO_DIR)

# manually added dependencies
REQUIRED_PACKAGES += web/php-83/php-common
REQUIRED_PACKAGES += library/pcre2

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
