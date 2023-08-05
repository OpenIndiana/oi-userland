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
# Copyright (c) 2023 Stephan Althaus
#

BUILD_BITS=		64
USE_OPENSSL11=		yes
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		php-8.1-ext-imagick
COMPONENT_VERSION=	3.7.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	ImageMagick for PHP
COMPONENT_PROJECT_URL=	https://pecl.php.net/package/imagick
COMPONENT_SRC=		imagick-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tgz
COMPONENT_ARCHIVE_HASH=	sha256:5a364354109029d224bcbb2e82e15b248be9b641227f45e63425c06531792d3e
COMPONENT_ARCHIVE_URL=	https://pecl.php.net/get/$(COMPONENT_SRC).tgz
COMPONENT_FMRI=		web/php-81/extension/php-imagick
COMPONENT_CLASSIFICATION=	Development/PHP
COMPONENT_LICENSE=	Apache v2.0
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CLEAN_PATHS +=  package.xml

PHP_PREFIX=/usr/php/8.1
PHP_SYSCONFDIR=/etc/php/8.1
PHP_DATADIR=/var/php/8.1

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

CONFIGURE_OPTIONS  +=	--build=x86_64-pc-solaris2.10
CONFIGURE_OPTIONS  +=	--with-php-config=$(PHP_PREFIX)/bin/php-config

CFLAGS             +=	-I$(PHP_PREFIX)/include
CPPFLAG            +=	$(CFLAGS)
LDFLAGS            +=	-L$(PHP_PREFIX)/lib/$(MACH64) -R$(PHP_PREFIX)/lib/$(MACH64)

CONFIGURE_SCRIPT   =	$(@D)/configure

COMPONENT_PRE_CONFIGURE_ACTION	 =	cp -R $(SOURCE_DIR)/* $(@D) ; cd $(@D) ; $(PHP_PREFIX)/bin/phpize
COMPONENT_PRE_BUILD_ACTION = ( sed -i 's/"tar/"gtar/g'  $(@D)/build/gen_stub.php ) 
#(mv $(@D)/build/PHP-Parser-4.13.0/PHP-Parser-4.13.0/PHP-Parser-4.13.0/* $(@D)/build/PHP-Parser-4.13.0/PHP-Parser-4.13.0/ )

COMPONENT_INSTALL_ARGS		+=	INSTALL_ROOT=$(PROTO_DIR)

# manually added dependencies
REQUIRED_PACKAGES += web/php-81/php-common

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += image/imagemagick
REQUIRED_PACKAGES += system/library
