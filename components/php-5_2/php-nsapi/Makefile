#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		php
COMPONENT_VERSION=	5.2.17
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:5ba7edcb5ea187687001c4ccdbb94ac48f77fa92
COMPONENT_ARCHIVE_URL=	http://us.php.net/get/$(COMPONENT_ARCHIVE)/from/this/mirror
#
# webserver7-spi only for php NSAPI
#
COMPONENT_NAME_1=	webserver7-spi
#COMPONENT_VERSION_1=	NONE
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_NAME_1).tar.bz2
COMPONENT_ARCHIVE_HASH_1= sha1:5bf9efa33fa8cab0e964c829196d084bc7a67015
#
# The Netscape server?
# Came from Sun's Netscape (web stack) group originally?
COMPONENT_ARCHIVE_URL_1= $(EXTERNAL_ARCHIVE_MIRROR)/$(COMPONENT_ARCHIVE_1)

PATCH_DIR = ../php-sapi/patches

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

include ../common.mk
include ../php-sapi/php.mk

COMPONENT_POST_UNPACK_ACTION += && ( \
	$(RM) -r $(COMPONENT_DIR)/$(COMPONENT_SRC_1); \
	cd $(COMPONENT_DIR); \
	$(UNPACK) $(UNPACK_ARGS) ./$(COMPONENT_ARCHIVE_1); \
	)

CONFIGURE_OPTIONS  += \
	--disable-all \
	$(COMMON_CONFIG_OPTIONS) \
	--with-config-file-path=$(CONF_DIR) \
	--with-config-file-scan-dir=$(CONF_DIR)/conf.d \
	--disable-cgi \
	--disable-fastcgi \
	--enable-discard-path \
	--enable-maintainer-zts \
	--enable-ftp=shared \
	--enable-pdo=shared \
	--with-bz2=shared \
	--with-curl=shared \
	--with-gd=shared \
	--with-gettext=shared \
	--with-iconv=shared \
	--with-imap=shared,$(IMAP_DIR) \
	--with-imap-ssl=shared,/usr \
	--with-ldap=shared \
	--with-mysql=shared,$(MYSQL_DIR) \
	--with-mysql-sock=/tmp/mysql.sock \
	--with-mysqli=shared,$(MYSQL_DIR)/bin/mysql_config \
	--with-nsapi=$(COMPONENT_DIR)/webserver7-spi \
	--with-openssl=shared \
	--with-pear=$(PEAR_DIR) \
	--with-pdo-mysql=shared,$(MYSQL_DIR) \
	--with-pdo-sqlite=shared \
	--with-snmp=shared,/usr \
	--with-sqlite=shared \
	--with-tidy=shared,/usr

CONFIGURE_ENV += $(ZTS_CONF_ENVLINE)

COMPONENT_POST_BUILD_ACTION = ( \
	cat $(BUILD_DIR_32)/scripts/phpize | \
	 sed -e "s,^\#!/bin/sh,\#!$(CONFIG_SHELL)," | \
	 sed -e "s%^prefix=.*%prefix=$(SOURCE_DIR)%" | \
	 sed -e "s%^includedir=.*%includedir=$(SOURCE_DIR)%" | \
	 sed -e "s%^phpdir=.*%phpdir=$(SOURCE_DIR)%"  | \
	 sed -e "s%phpdir/phpize.m4%phpdir/scripts/phpize.m4%" | \
	 sed -e 's%cd "$$phpdir" && cp $$FILES_BUILD "$$builddir"/build%cd "$$phpdir/build" \&\& cp $$FILES_BUILD "$$builddir"/build%' \
	 > phpize-proto.zts ; \
	chmod 755 phpize-proto.zts )

ADD_NSAPI_MODULE_SUPPORT = ( \
	$(MKDIR) $(PROTO_DIR)/$(TOP_DIR)/nsapi/; \
	$(CP) $(BUILD_DIR_32)/libs/libphp5.so \
		$(PROTO_DIR)/$(TOP_DIR)/nsapi/libphp5.so; \
	)

FIX_CONFIG_FILES = ( \
	cd $(COMPONENT_DIR); \
	$(GSED) -e "s@extension_dir = \(.*\)@extension_dir=$(PHP_ROOT_ZTS_EXT)@"< ../php-sapi/build/prototype/$(MACH)/$(CONFDIR)/php.ini > php.ini; \
	$(MKDIR) $(PROTO_DIR)/$(NSAPI_CONFDIR); \
	$(INSTALL) -m 644 php.ini $(PROTO_DIR)/$(NSAPI_CONFDIR); \
	)

COMPONENT_INSTALL_TARGETS = libphp5.la install-modules

COMPONENT_POST_INSTALL_ACTION = ( \
	$(ADD_NSAPI_MODULE_SUPPORT); \
	$(FIX_CONFIG_FILES); \
	)

CLEAN_PATHS += webserver7-spi phpize-proto.zts php.ini

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

# php-sapi does the publish
publish:	install

## causes loop in gmake
##../php-sapi/build/$(MACH32)/.installed:
##	(cd ../php-sapi ; $(MAKE) install)
##
##$(BUILD_DIR_32)/.configured:	../php-sapi/build/$(MACH32)/.installed

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
