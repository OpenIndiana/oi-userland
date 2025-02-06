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
# Copyright (c) 2022 Niklas Poslovski
# Copyright (c) 2024 Friedrich Kink
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		php-8.3-ext-yaml
COMPONENT_REAL_NAME=	yaml
COMPONENT_VERSION=	2.2.4
COMPONENT_SRC=		$(COMPONENT_REAL_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://pecl.php.net/package/$(COMPONENT_REAL_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_REAL_NAME)-$(COMPONENT_VERSION).tgz
COMPONENT_ARCHIVE_HASH=	sha256:8eb353baf87f15b1b62ac6eb71c8b589685958a1fe8b0e3d22ac59560d0e8913
COMPONENT_ARCHIVE_URL=	https://pecl.php.net/get/$(COMPONENT_ARCHIVE)
COMPONENT_SUMMARY=	php memcache extension
COMPONENT_FMRI=		web/php-83/extension/php-yaml
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_CLASSIFICATION=	Development/PHP

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_TARGETS = test

COMPONENT_TEST_ENV += NO_INTERACTION=yes

COMPONENT_TEST_TRANSFORMS += \
    '-e "/^make/d" ' \
    '-e "/^Time taken/d" ' \
    '-e "/^TEST RESULT SUMMARY$$/,\$$p" ' \
    '-e "/.*/d" '

CLEAN_PATHS +=  package.xml

PHP_PREFIX=/usr/php/8.3
PHP_SYSCONFDIR=/etc/php/8.3
PHP_DATADIR=/var/php/8.3

CONFIGURE_SCRIPT	=      $(BUILD_DIR)/$(MACH64)/configure

# Configure Options
CONFIGURE_OPTIONS	=    --prefix=$(PHP_PREFIX)
CONFIGURE_OPTIONS	+=   --bindir=$(PHP_PREFIX)/bin
CONFIGURE_OPTIONS	+=   --sbindir=$(PHP_PREFIX)/bin
CONFIGURE_OPTIONS	+=   --libdir=$(PHP_PREFIX)/lib/$(MACH64)
CONFIGURE_OPTIONS	+=   --libexecdir=$(PHP_PREFIX)/libexec
CONFIGURE_OPTIONS	+=   --includedir=$(PHP_PREFIX)/include
CONFIGURE_OPTIONS	+=   --sysconfdir=$(PHP_SYSCONFDIR)
CONFIGURE_OPTIONS	+=   --datadir=$(PHP_DATADIR)
CONFIGURE_OPTIONS	+=   --mandir=$(PHP_PREFIX)/share/man
CONFIGURE_OPTIONS	+=   --localstatedir=$(PHP_DATADIR)

CONFIGURE_OPTIONS	+=   --build=x86_64-pc-solaris2.10
CONFIGURE_OPTIONS	+=   --with-php-config=$(PHP_PREFIX)/bin/php-config

CFLAGS                +=	-I$(PHP_PREFIX)/include
CPPFLAGS              +=	$(CFLAGS)
LDFLAGS		      +=	-L$(PHP_PREFIX)/lib/$(MACH64) -R$(PHP_PREFIX)/lib/$(MACH64)

CONFIGURE_OPTIONS     +=        CC="$(CC)" CXX="$(CXX)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"

COMPONENT_PRE_CONFIGURE_ACTION	 =	cp -R $(SOURCE_DIR)/* $(@D) ; cd $(@D) ; $(PHP_PREFIX)/bin/phpize
COMPONENT_INSTALL_ARGS		+=	INSTALL_ROOT=$(PROTO_DIR)

# manually added dependencies
REQUIRED_PACKAGES += web/php-83/php-common

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libyaml
REQUIRED_PACKAGES += system/library
