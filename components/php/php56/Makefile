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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
COMPILER= gcc
include ../../../make-rules/shared-macros.mk

include $(WS_COMPONENTS)/php/php-metadata.mk

COMPONENT_NAME=		php
COMPONENT_VERSION=	$(UL_PHP_VERSION)
COMPONENT_PROJECT_URL=	http://php.net/
COMPONENT_SRC=		$(PHP_COMPONENT_SRC)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=\
    sha256:07187ba2870f89cef334cd2ad6cb801aeec5eaf283da0293a9a6be75d6786d11
COMPONENT_ARCHIVE_URL=	http://php.net/get/$(COMPONENT_ARCHIVE)/from/this/mirror
TPNO=			32826

include $(WS_MAKE_RULES)/common.mk
include $(PHP_TOP_DIR)/php.mk

# need GCC_ROOT/bin for configure, usr/sbin for dtrace 
export PATH=$(GCC_ROOT)/bin:$(USRBINDIR):$(USRSBINDIR):$(GNUBIN)

# We patch configure.in to allow building just modules (no SAPI's), e.g. intl.
# Since we are sharing the source, regenerate configure here.
COMPONENT_PREP_ACTION += (cd $(SOURCE_DIR) ; autoreconf) ;

include enable-extensions.mk

CONFIGURE_OPTIONS += --enable-dtrace

# Without this, the the build seems to interrogate GCC for potential library
# search path information and then embed it into the RUNPATH of selected ELF
# files it creates.  This includes GCC private directories
CONFIGURE_OPTIONS += --disable-rpath

ETCPHPDIR= $(ETCDIR)/php/$(UL_PHP_MINOR_VERSION)
VARPHPDIR= $(VARDIR)/php/$(UL_PHP_MINOR_VERSION)
# .conf files go under /etc, not /usr
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCPHPDIR)
# var doesn't go under /usr either!
CONFIGURE_OPTIONS +=	--localstatedir=$(VARPHPDIR)
# Nor does php.ini and its friends.
CONFIGURE_OPTIONS +=	--with-config-file-path=$(ETCPHPDIR)
CONFIGURE_OPTIONS +=	--with-config-file-scan-dir=$(ETCPHPDIR)/conf.d
# Nor does PEAR (default: $PREFIX/lib/php)
CONFIGURE_OPTIONS +=	--with-pear=$(VARPHPDIR)/pear

# icu's switch to g++
# 21090206 icu should build C++ to C++11
# Causes this in php forcing php to switch also
# 23003672 PHP fails all or most tests
CXXFLAGS += -std=c++11
CONFIGURE_OPTIONS += CXXFLAGS="$(CXXFLAGS)"

# Use openldap
# This is good enough to fool configure
CPPFLAGS += -I$(USRINCDIR)/openldap
LDFLAGS += -lldap_r
# but ensure "make" gets the point
COMPONENT_BUILD_ARGS += LDAP_SHARED_LIBADD="-lldap_r"

# Disable SSLv2 and SSLv3 for security reasons
CFLAGS += -DOPENSSL_NO_SSL2
CFLAGS += -DOPENSSL_NO_SSL3

PROTOUSRPHPVERDIR = $(PROTO_DIR)/$(CONFIGURE_PREFIX)
# Adapted from PHP 5.3 Makefile.
# Creates alternate versions of the scripts needed for building extensions
# separately, since the generated versions of these scripts hardcode configuring
# for a PHP that is installed on the system.
COMPONENT_POST_INSTALL_ACTION += \
	( set -e; \
	mkdir -p proto-scripts; \
	cat $(BUILD_DIR_64)/scripts/phpize | \
	 sed -e "s,^\#!/bin/sh,\#!$(CONFIG_SHELL)," | \
	 sed -e "s%^prefix=.*%prefix=$(PROTOUSRPHPVERDIR)%" | \
	 sed -e "s%^includedir=.*%includedir=$(PROTOUSRPHPVERDIR)/include/php%" | \
	 sed -e "s%^phpdir=.*%phpdir=$(SOURCE_DIR)%"  | \
	 sed -e "s%phpdir/phpize.m4%phpdir/scripts/phpize.m4%" | \
	 sed -e "s%$PHP_AUTOCONF   || exit 1%$PHP_AUTOCONF -f   || exit 1%" | \
	 sed -e "s%$PHP_AUTOHEADER || exit 1%$PHP_AUTOHEADER -f || exit 1%" | \
	 sed -e 's%(cd "$$phpdir" && cp $$FILES_BUILD "$$builddir"/build)%(cd "$$phpdir/build" \&\& cp $$FILES_BUILD "$$builddir"/build)%' | \
	 sed -e "s%^builddir=.*%builddir=$(BUILD_DIR_64)%" \
	 > proto-scripts/phpize-proto ; \
	chmod 755 proto-scripts/phpize-proto ) ; \
	( set -e; \
	 cat $(BUILD_DIR_64)/scripts/php-config | \
	 sed -e "s,^\#! /bin/sh,\#!$(CONFIG_SHELL)," | \
	 sed -e "s%^prefix=.*%prefix=$(PROTOUSRPHPVERDIR)%" | \
	 sed -e "s%^include_dir=.*%include_dir=$(PROTOUSRPHPVERDIR)/include/php%" \
	 > proto-scripts/php-config-proto ; \
	chmod 755 proto-scripts/php-config-proto ) ;

# test failures; keep going
COMPONENT_TEST_ARGS += -k -i
# different results for different architectures
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH)-$(BITS).master
COMPONENT_TEST_TRANSFORMS += \
    '-e "/^make/d" '

CLEAN_PATHS += proto-scripts

# The test results are unstable between runs
$(SKIP_TEST_AT_TOP_LEVEL)

REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += library/libxml2
$(SOLARIS_11_ONLY)REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/dtrace
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += system/network/ldap/openldap
REQUIRED_PACKAGES += text/gnu-sed
