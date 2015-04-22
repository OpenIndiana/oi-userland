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
# Copyright (c) 2012, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		php
COMPONENT_VERSION=	5.3.29
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:c4e1cf6972b2a9c7f2777a18497d83bf713cdbecabb65d3ff62ba441aebb0091
COMPONENT_ARCHIVE_URL=	http://us.php.net/get/$(COMPONENT_ARCHIVE)/from/this/mirror
COMPONENT_PROJECT_URL=	http://www.php.net/

#
# webserver7-spi only for php NSAPI
#
COMPONENT_NAME_1=	webserver7-spi
#COMPONENT_VERSION_1=	NONE
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_NAME_1).tar.bz2
COMPONENT_ARCHIVE_HASH_1= \
    sha256:9739fe99ed270955546313322775940c6b7e8eb802707d248342406ebe5b1c97
#
# The Netscape server?
# Came from Sun's Netscape (web stack) group originally?
COMPONENT_ARCHIVE_URL_1= $(EXTERNAL_ARCHIVE_MIRROR)/$(COMPONENT_ARCHIVE_1)

PATCH_DIR = ../php-sapi/patches

include ../php-sapi/php.mk

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

include ../common.mk

COMPONENT_POST_UNPACK_ACTION += && ( \
	set -e; \
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
	--with-mysql=shared,mysqlnd \
	--with-mysql-sock=/tmp/mysql.sock \
	--with-mysqli=shared,mysqlnd \
	--with-nsapi=$(COMPONENT_DIR)/webserver7-spi \
	--with-openssl=shared \
	--with-pear=$(PEAR_DIR) \
	--with-pdo-mysql=shared,mysqlnd \
	--with-pdo-sqlite=shared \
	--with-snmp=shared,/usr \
	--with-sqlite3=shared \
	--with-tidy=shared,/usr

CONFIGURE_ENV += $(ZTS_CONF_ENVLINE)

COMPONENT_POST_BUILD_ACTION = ( \
	set -e; \
	cat $(BUILD_DIR_32)/scripts/phpize | \
	 sed -e "s,^\#!/bin/sh,\#!$(CONFIG_SHELL)," | \
	 sed -e "s%^prefix=.*%prefix=$(BUILD_DIR_32)%" | \
	 sed -e "s%^includedir=.*%includedir=$(BUILD_DIR_32)%" | \
	 sed -e "s%^phpdir=.*%phpdir=$(BUILD_DIR_32)%"  | \
	 sed -e "s%phpdir/phpize.m4%phpdir/scripts/phpize.m4%" | \
	 sed -e 's%cd "$$phpdir" && cp $$FILES_BUILD "$$builddir"/build%cd "$$phpdir/build" \&\& cp $$FILES_BUILD "$$builddir"/build%' \
	 > phpize-proto.zts ; \
	chmod 755 phpize-proto.zts )

ADD_NSAPI_MODULE_SUPPORT = ( \
	set -e; \
	$(MKDIR) $(PROTO_DIR)/$(TOP_DIR)/nsapi/; \
	$(CP) $(BUILD_DIR_32)/libs/libphp5.so \
		$(PROTO_DIR)/$(TOP_DIR)/nsapi/libphp5.so; \
	)

FIX_CONFIG_FILES = ( \
	set -e; \
	cd $(COMPONENT_DIR); \
	$(GSED) -e "s@extension_dir = \(.*\)@extension_dir=$(PHP_ROOT_ZTS_EXT)@"< ../php-sapi/build/prototype/$(MACH)/$(CONFDIR)/php.ini > php.ini; \
	$(MKDIR) $(PROTO_DIR)/$(NSAPI_CONFDIR); \
	$(INSTALL) -m 644 php.ini $(PROTO_DIR)/$(NSAPI_CONFDIR); \
	)

COMPONENT_INSTALL_TARGETS = libphp5.la install-modules

COMPONENT_POST_INSTALL_ACTION = ( \
	set -e; \
	$(ADD_NSAPI_MODULE_SUPPORT); \
	$(FIX_CONFIG_FILES); \
	)

CLEAN_PATHS += webserver7-spi phpize-proto.zts php.ini

# Test results not quite stable but good enough for human eyes
$(SKIP_TEST_AT_TOP_LEVEL)

configure:	$(CONFIGURE_32)

build:		$(BUILD_32)

install:	$(INSTALL_32)

# These test and compare results are not quite stable enough
# to use in automated testing but good enough to eye 
# ball and get a sense that php is working correctly.
# Individual tests can be run afterwards.
# Several random tests may PASS/FAIL on each run thus invalidating
# test and compare results.
# To use the master test result file do:
# $ gmake build
# $ gmake -i -k test
# because very likely the comparison phase will fail.

# test failures; keep going
COMPONENT_TEST_ARGS += -k -i

# different results for different architectures
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH$(BITS)).master

test:		$(TEST_32)

# php-sapi does the publish
publish:	install
