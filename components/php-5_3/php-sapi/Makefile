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
# Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

# NOTE:
#    Currently the version numbers in the package manifests, one
#    level up, are manually set because the COMPONENT_VERSION, like
#    below, is not available at the top level where this is IPS
#    published from.

COMPONENT_NAME=		php
COMPONENT_VERSION=	5.3.14
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:c8075b6e83c5db0d26cc8426a7456856421089a76c963813b1fcac3ced041cb3
COMPONENT_ARCHIVE_URL=	http://us.php.net/get/$(COMPONENT_ARCHIVE)/from/this/mirror
COMPONENT_PROJECT_URL=	http://www.php.net/

#
# php documentation
COMPONENT_NAME_1=       php_manual_en
COMPONENT_VERSION_1=	20120717
COMPONENT_SRC_1=        $(COMPONENT_NAME_1)_$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=    $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:4c5d45e5f49bb164d40154fdef57b3193e7b77e306055559e60615c8ca9a3c30
#
# This next download URL is completely hocus pocus.
# php.net does not freeze their documentation to match the software versions.
# So we need to take a snapshot of PHP's documentation by downloading what
# they currently have from this URL:
# COMPONENT_ARCHIVE_URL_1=http://us.php.net/get/php_manual_en.tar.gz/from/this/mirror
# Then move that download to the name being constructed in the variables
# above.  Finally, forward a copy to the gatekeeping staff to place
# the copy in userland's download cache so that the following download URL
# will pick it up.
COMPONENT_ARCHIVE_URL_1=http://us.php.net/get/$(COMPONENT_ARCHIVE_1)/from/this/mirror

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

include ../common.mk
include ./php.mk

CONFIGURE_OPTIONS  += \
	$(COMMON_CONFIG_OPTIONS) \
	--disable-cgi \
	--disable-fastcgi \
	--enable-discard-path \
	--enable-ftp=shared \
	--enable-pdo=shared \
	--with-apxs2=$(APACHE_USR_PREFIX)/bin/apxs \
	--with-bz2=shared \
	--with-config-file-path=$(CONF_DIR) \
	--with-config-file-scan-dir=$(MODULES_CONF_DIR) \
	--with-curl=shared \
	--with-curlwrappers \
	--with-gd=shared \
	--with-gettext=shared \
	--with-iconv=shared \
	--with-imap=shared,$(IMAP_DIR) \
	--with-imap-ssl=shared,/usr \
	--with-ldap=shared \
	--with-mysql=shared,$(MYSQL_DIR) \
	--with-mysql-sock=/tmp/mysql.sock \
	--with-mysqli=shared,$(MYSQL_DIR)/bin/mysql_config \
	--with-openssl=shared \
	--with-pear=$(PEAR_DIR) \
	--with-pdo-mysql=shared,$(MYSQL_DIR) \
	--with-pdo-sqlite=shared \
	--with-snmp=shared,/usr \
	--with-sqlite=shared \
	--with-tidy=shared,/usr \
	--without-tsrm-pthreads

CONFIGURE_ENV += $(CONF_ENVLINE)

COMPONENT_POST_BUILD_ACTION = ( \
	cat $(BUILD_DIR_32)/scripts/phpize | \
	 sed -e "s,^\#!/bin/sh,\#!$(CONFIG_SHELL)," | \
	 sed -e "s%^prefix=.*%prefix=$(SOURCE_DIR)%" | \
	 sed -e "s%^includedir=.*%includedir=$(SOURCE_DIR)%" | \
	 sed -e "s%^phpdir=.*%phpdir=$(SOURCE_DIR)%"  | \
	 sed -e "s%phpdir/phpize.m4%phpdir/scripts/phpize.m4%" | \
	 sed -e "s%$PHP_AUTOCONF   || exit 1%$PHP_AUTOCONF -f   || exit 1%" | \
	 sed -e "s%$PHP_AUTOHEADER || exit 1%$PHP_AUTOHEADER -f || exit 1%" | \
	 sed -e 's%(cd "$$phpdir" && cp $$FILES_BUILD "$$builddir"/build)%(cd "$$phpdir/build" \&\& cp $$FILES_BUILD "$$builddir"/build)%' | \
	 sed -e "s%^builddir=.*%builddir=$(BUILD_DIR_32)%" \
	 > phpize-proto ; \
	chmod 755 phpize-proto ) ; \
	( cat $(BUILD_DIR_32)/scripts/php-config | \
	 sed -e "s,^\#! /bin/sh,\#!$(CONFIG_SHELL)," | \
	 sed -e "s%^prefix=.*%prefix=$(SOURCE_DIR)%" | \
	 sed -e "s%^include_dir=.*%include_dir=$(SOURCE_DIR)%" \
	 > php-config-proto ; \
	chmod 755 php-config-proto ) ; \
	( cat $(BUILD_DIR_32)/scripts/php-config | \
	 sed -e "s,^\#! /bin/sh,\#!$(CONFIG_SHELL)," | \
	 sed -e "s%^prefix=.*%prefix=$(COMPONENT_DIR)/../php-nsapi/$(COMPONENT_SRC)%" | \
	 sed -e "s%^include_dir=.*%include_dir=$(COMPONENT_DIR)/../php-nsapi/$(COMPONENT_SRC)%" | \
	 sed -e "s%^extension_dir=.*%extension_dir=$(ZTS_MODULES_DIR)%" \
	 > php-config-proto.zts ; \
	chmod 755 php-config-proto.zts )

ADD_APACHE2_MODULE_SUPPORT = ( \
	$(MKDIR) $(PROTO_DIR)/$(APACHE2_PHP); \
	$(INSTALL) -m 0644 $(COMPONENT_DIR)/../Solaris/php$(PHP_REL).conf \
		$(PROTO_DIR)/$(APACHE2_PHP)/php$(PHP_REL).conf; \
	$(GSED) -i -e "s@<<VERSION>>@$(PHP_REL)@g" \
		$(PROTO_DIR)/$(APACHE2_PHP)/php$(PHP_REL).conf; \
	$(SYMLINK) php$(PHP_REL).conf \
	                $(PROTO_DIR)/$(APACHE2_PHP)/php.conf; \
	$(CP) $(PROTO_DIR)/$(APACHE2_EXTDIR)/libphp5.so \
		$(PROTO_DIR)/$(APACHE2_EXTDIR)/mod_php$(PHP_REL).so; \
	)

# Ship a default php.ini to simplify ease of use.
FIX_CONFIG_FILES = ( \
	cd $(SOURCE_DIR); \
	$(GPATCH) -p0 -o php.ini-patched -i ../patches-other/php_ini.patch; \
	$(GSED) -e "s@<<VERSION>>@$(PHP_REL)@g" < php.ini-patched > php.ini; \
	$(INSTALL) -m 644 php.ini $(PROTO_DIR)/$(CONF_DIR)/php.ini; \
	)

INSTALL_DOCS = ( \
	$(MKDIR) $(PROTO_DIR)/$(DOCDIR); \
	$(UNPACK) -r $(PROTO_DIR)/$(DOCDIR) $(COMPONENT_ARCHIVE_1); \
	)

INSTALL_SAMPLES = ( \
	$(MKDIR) $(PROTO_DIR)/$(SCRIPTS_DIR); \
	$(MKDIR) $(COMPONENT_DIR)/tmp; \
	cd $(COMPONENT_DIR); \
	$(GSED) -e "s,\<\<INSTALL_DIR\>\>,$(PHP_ROOT)," \
		-e "s,\<\<CONF_DIR\>\>,$(CONFDIR)," \
		-e "s,\<\<NSAPI_CONF_DIR\>\>,$(NSAPI_CONFDIR)," \
		-e "s,\<\<MODULES_CONF_DIR\>\>,$(MODULES_CONFDIR)," \
		-e "s,\<\<ZTS_MODULES_CONF_DIR\>\>,$(ZTS_MODULES_CONFDIR)," \
		< $(COMPONENT_DIR)/../Solaris/configure-sun-webserver \
		> tmp/tmp; \
	$(INSTALL) -m 555 tmp/tmp \
		$(PROTO_DIR)/$(SCRIPTS_DIR)/configure-sun-webserver; \
	cd $(PROTO_DIR)/$(PHP_BIN); \
	$(RM) configure-webserver7; \
	$(SYMLINK) ../samples/scripts/configure-sun-webserver \
						configure-webserver7; \
	)

# patch installation to support pear installation.
PATCH_PEAR = ( \
	cd $(PROTO_DIR)/$(PHP_BIN); \
	$(GPATCH) -N -i $(COMPONENT_DIR)/patches-other/pear_pecl.patch; \
	$(GPATCH) -N -i $(COMPONENT_DIR)/patches-other/pear_php_config.patch; \
	cd $(PROTO_DIR)/$(PHP_LIB)/build; \
	$(GPATCH) -N -i $(COMPONENT_DIR)/patches-other/pear_Makefile_global.patch; \
	cd $(PROTO_DIR)/$(PEAR_DIR); \
	$(GPATCH) -N -p0 -i $(COMPONENT_DIR)/patches-other/pear_Builder_php.patch; \
	$(CP) $(COMPONENT_DIR)/config/pear/*.reg \
					$(PROTO_DIR)/$(PEAR_DIR)/.channels/;  \
	)

# Create symbolic links
# Not strictly necessary but makes the proto area more correct.
CREATE_SYMLINKS = ( \
	cd $(PROTO_DIR)/usr/php; \
	$(RM) bin lib include modules doc man; \
	$(SYMLINK) $(PHP_REL)/bin . ; \
	$(SYMLINK) $(PHP_REL)/lib . ; \
	$(SYMLINK) $(PHP_REL)/include . ; \
	$(SYMLINK) $(PHP_REL)/modules . ; \
	$(SYMLINK) $(PHP_REL)/doc . ; \
	$(SYMLINK) $(PHP_REL)/man . ; \
	$(MKDIR) $(PROTO_DIR)/usr/bin; \
	cd $(PROTO_DIR)/usr/bin; \
	$(RM) php php-config phpize; \
	$(SYMLINK) ../php/$(PHP_REL)/bin/php . ; \
	$(SYMLINK) ../php/$(PHP_REL)/bin/php-config . ; \
	$(SYMLINK) ../php/$(PHP_REL)/bin/phpize . ; \
	$(SYMLINK) ../php/$(PHP_REL)/bin/phar . ; \
	)

COMPONENT_POST_INSTALL_ACTION = ( \
	$(ADD_APACHE2_MODULE_SUPPORT); \
	$(FIX_CONFIG_FILES); \
	$(FIX_CONFIG_FILES_2); \
	$(INSTALL_DOCS); \
	$(INSTALL_SAMPLES); \
	$(PATCH_PEAR); \
	$(CREATE_SYMLINKS); \
	)

# This package contains all 3 versions of php:
#	sapi, cgi, nsapi
PKG_PROTO_DIRS += $(COMPONENT_DIR)/../php-nsapi/build/prototype/$(MACH)
PKG_PROTO_DIRS += $(COMPONENT_DIR)/../php-cgi/build/prototype/$(MACH)

CLEAN_PATHS += phpize-proto php-config-proto php-config-proto.zts tmp
CLEAN_PATHS += php.ini-patched

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32) PHP-NSAPI_INSTALL PHP-CGI_INSTALL

# Besides running this test target it is also strong advised to download
# and test with:
# Joomla!	http://www.joomla.org/
# WordPress	http://wordpress.org/
test:		$(TEST_32)

../imap/build/$(MACH32)/.built:
	(cd ../imap ; $(MAKE) build)

../php-nsapi/build/$(MACH32)/.installed:
	(cd ../php-nsapi ; $(MAKE) install)

../php-cgi/build/$(MACH32)/.installed:
	(cd ../php-cgi ; $(MAKE) install)

$(BUILD_DIR_32)/.configured:	../imap/build/$(MACH32)/.built
PHP-NSAPI_INSTALL:		../php-nsapi/build/$(MACH32)/.installed
PHP-CGI_INSTALL:		../php-cgi/build/$(MACH32)/.installed

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
