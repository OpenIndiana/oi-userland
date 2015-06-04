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

#
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

# This file specifies configure-line options to enable as many extensions as
# possible, and specifies their dependencies and anything else that's required.

# As of PHP 5.6.3:
# The following "extensions" are always statically compiled into PHP:
#    Core date ereg pcre Reflection SPL standard
# The following are statically compiled unless --disable-all is used:
#    ctype dom fileinfo filter hash iconv json libxml PDO pdo_sqlite Phar posix
#    session SimpleXML sqlite3 tokenizer xml xmlreader xmlwriter
# The following is compiled as a shared extension unless --disable-all is used:
#    opcache

# The PHP build system allows building binaries for CLI, CGI, FPM, and one SAPI,
# at once.
# More than one SAPI (e.g. Apache and NSAPI) is not allowed. Since the only
# SAPI we deliver is Apache, only one build is necessary.

# CLI and CGI are enabled by default.

CONFIGURE_OPTIONS += --enable-fpm

# Apache SAPI.
CONFIGURE_OPTIONS += --with-apxs2=/usr/apache2/2.4/bin/apxs
# Prevent gmake install telling apxs to modify httpd.conf, which doesn't exist.
COMPONENT_PRE_CONFIGURE_ACTION += \
	$(GSED) -i -e "s/-i -a -n php5/-i -n php5/" $(CONFIGURE_SCRIPT) ;
REQUIRED_PACKAGES += web/server/apache-24


# Sometimes extensions can't find necessary library headers. This is often
# because Solaris has installed them in /usr/include/foo/bar.h instead of
# directly at /usr/include/bar.h, in which case you must patch the config.m4.

# Statically compiled (and non-default) extensions, with reasons:
CONFIGURE_OPTIONS += --with-zlib	# Dependency of mysqlnd, else link error
REQUIRED_PACKAGES += library/zlib

# Shared extensions (creates runtime-loadable modules, enable them in *.ini):

CONFIGURE_OPTIONS += --with-mysql=shared,mysqlnd
CONFIGURE_OPTIONS += --with-mysqli=shared,mysqlnd
CONFIGURE_OPTIONS += --with-pdo-mysql=shared,mysqlnd
# Note that using the MySQL Native Driver (mysqlnd), there is no dependency on
# having MySQL installed locally.
CONFIGURE_OPTIONS += --with-mysql-sock=/tmp/mysql.sock

CONFIGURE_OPTIONS += --enable-bcmath=shared

CONFIGURE_OPTIONS += --with-bz2=shared
REQUIRED_PACKAGES += compress/bzip2

CONFIGURE_OPTIONS += --enable-calendar=shared

CONFIGURE_OPTIONS += --with-curl=shared
REQUIRED_PACKAGES += web/curl

CONFIGURE_OPTIONS += --enable-dba=shared
CONFIGURE_OPTIONS += --with-db4	# Oracle Berkeley DB
CONFIGURE_OPTIONS += --with-cdb	# another database (internal support)
REQUIRED_PACKAGES += database/berkeleydb-5

CONFIGURE_OPTIONS += --with-enchant=shared
REQUIRED_PACKAGES += library/spell-checking/enchant

CONFIGURE_OPTIONS += --enable-exif=shared

CONFIGURE_OPTIONS += --enable-ftp=shared

CONFIGURE_OPTIONS += --with-gettext=shared

CONFIGURE_OPTIONS += --with-gd=shared
CONFIGURE_OPTIONS += --enable-gd-jis-conv
CONFIGURE_OPTIONS += --enable-gd-native-ttf
# libz and libpng are found without help.
# libxpm, libjpeg, and freetype need help.
# libvpx and t1lib don't exist on Solaris.
CONFIGURE_OPTIONS += --with-freetype-dir=/usr
CONFIGURE_OPTIONS += --with-xpm-dir=/usr
CONFIGURE_OPTIONS += --with-jpeg-dir=/usr
REQUIRED_PACKAGES += x11/library/libxpm
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += library/zlib

CONFIGURE_OPTIONS += --with-gmp=shared		# patched config.m4
REQUIRED_PACKAGES += library/gmp

CONFIGURE_OPTIONS += --enable-intl=shared
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += system/library/math
CONFIGURE_ENV +=	CXXFLAGS="$(CXXFLAGS)"
# For intl, libtool(?) insists on passing "-lCrun -lCstd". These are
# legacy Solaris/Studio C++ runtime and standard libraries, which is wrong.
# Remove these flags by editing the generated Makefile after configure runs.
COMPONENT_POST_CONFIGURE_ACTION += \
	$(GSED) -i -e 's/-lCrun//g' -e 's/-lCstd//g' $(BUILD_DIR_64)/Makefile

CONFIGURE_OPTIONS += --with-ldap=shared

CONFIGURE_OPTIONS += --enable-mbstring=shared

CONFIGURE_OPTIONS += --with-openssl=shared
CONFIGURE_OPTIONS += --with-kerberos		# WARNING! imap reads same flag!
REQUIRED_PACKAGES += library/security/openssl

CONFIGURE_OPTIONS += --enable-pcntl=shared

CONFIGURE_OPTIONS += --with-readline=shared
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/ncurses

CONFIGURE_OPTIONS += --enable-shmop=shared

CONFIGURE_OPTIONS += --with-snmp=shared
REQUIRED_PACKAGES += system/management/snmp/net-snmp

CONFIGURE_OPTIONS += --enable-soap=shared

CONFIGURE_OPTIONS += --enable-sockets=shared

CONFIGURE_OPTIONS += --enable-sysvsem=shared

CONFIGURE_OPTIONS += --enable-sysvshm=shared

CONFIGURE_OPTIONS += --enable-sysvmsg=shared

CONFIGURE_OPTIONS += --with-tidy=shared
REQUIRED_PACKAGES += text/tidy

CONFIGURE_OPTIONS += --enable-wddx=shared

CONFIGURE_OPTIONS += --with-xmlrpc=shared

CONFIGURE_OPTIONS += --with-xsl=shared
REQUIRED_PACKAGES += library/libxslt

CONFIGURE_OPTIONS += --enable-zip=shared

# Special cases

# IMAP: commented out until IMAP library itself is approved
#CONFIGURE_OPTIONS += --with-imap=shared,$(PHP_TOP_DIR)/uw-imap/build/$(MACH64)
#CONFIGURE_OPTIONS += --with-imap-ssl=shared,/usr
#CONFIGURE_OPTIONS += --with-kerberos	# WARNING! openssl reads same flag!
#COMPONENT_PRE_CONFIGURE_ACTION += (cd $(PHP_TOP_DIR)/uw-imap ; gmake build) ;

# Enables emulation of the obsolete mhash extension by the hash extension.
CONFIGURE_OPTIONS += --with-mhash

# Use system PRCE library instead of default bundled one, on Solaris principles.
CONFIGURE_OPTIONS += --with-pcre-dir=/usr

# List of extensions not enabled, with reasons:
# com_dotnet		Windows-only
# dbase			removed from the PHP distribution into PECL
# firebird/interbase	depends on software that is not in Solaris
# frontbase/fbsql	depends on software that is not in Solaris
# informix		removed to PECL; depends on sw that is not in Solaris
# mcrypt		libmcrypt is being EOF'ed in Solaris
# mssql			depends on software that is not in Solaris (FreeTDS)
# msql			depends on software that is not in Solaris
# postgresql/pgsql	depends on software that is not in Solaris
# pspell		depends on software that is not in Solaris
# recode		depends on software that is not in Solaris
# sybase		depends on software that is not in Solaris

# pdo_* except as noted	depend on software that is not in Solaris

# nsapi			being evaluated
# pdo_oci		being evaluated
# unixodbc, pdo_odbc	being evaluated
