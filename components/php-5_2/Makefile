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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk
include ../../make-rules/ips.mk

##
## This Makefile for local usage only.
## The full build will NOT execute this Makefile.
##

# PHP 5.2
#
# Build ordering:
#	1) imap		-> install
#	2) php-sapi	-> install
#	3) php-nsapi	-> install
#	3) php-cgi	-> install
#	4) php-sapi	-> publish (packages sapi, nsapi, cgi in 1 package)
#	5) APC-zts	-> install
#	6) APC		-> publish (packages APC-zts, APC in 1 package)
#	5) idn-zts	-> install
#	6) idn		-> publish (packages idn-zts, idn in 1 package)
#	5) memcache-zts -> install
#	6) memcache     -> publish (packages memcache-zts, memcache in 1 pack)
#	5) suhosin-zts  -> install
#	6) suhosin      -> publish (packages suhosin-zts, suhosin in 1 package)
#	5) tcpwrap-zts  -> install
#	6) tcpwrap	-> publish (packages tcpwrap-zts, tcpwrap in 1 package)
#	5) xdebug-zts	-> install
#	6) xdebug	-> publish (packages xdebug-zts, xdebug in 1 package)
#
# The numbers indicate parallelism possible in the build.
# The other way to build this would be:
#	1) imap		-> build
#	2) php-sapi	-> install
#	3) php-nsapi	-> install
#	4) all others	-> install (in parallel)
#	5) all		-> publish (in parallel)
# So after imap, php-sapi, php-nsapi build serially in that order
# then it doesn't matter.

# PHP is built 3 ways:
#	php-sapi  - Server API
#	php-cgi   - CGI
#	php-nsapi - Netscape Server API
#		    This is the Netscape group (aka webstack group)
#		    that Sun purchased from AOL long ago.
#		    I believe this Netscape server is still alive
#		    and offered by Oracle.
# These PHP's are built from the same source, patched the same way,
# but configured differently.

# More relevant to the full USERLAND build is the dependency tree
# for say starting the build down in an extension module:
# To publish the APC extension:
# 	1) build imap
#	2) install php-sapi
#	3) install APC
#	4) install php-nsapi
#	5) install APC-zts
#	6) publish APC

# SFW build of php
# 1) build_imap - Because php needs headers and libc-client.a
#                 Must be built first.
# 2) build_modphp5 - php SAPI
#        $(PHP_DIR)/libs/libphp5.so
#              $(PHP_DIR)/config.status
#                    $(PHP_DIR)/configure
#                          unroll php archive
#                          patch
#                          ./buildconf
#                          edit configure
#                          copy php source tree for php_fast/cgi build
#                          unroll webserver7-spi
#                              [Sun Java System Web Server 7 (formerly known
#                               as Sun ONE/iPlanet Enterprise Server)]
#                              [now Oracle iPlanet Web Server 7]
#                          copy php source tree for php_nsapi build
#                    $(PHP_NSAPI)/configure
#                        [stuff...]
#                    ./configure
# 3) build_cgi     - php cgi/fastcgi
# 4) build_nsapi   - php nsapi (netscape SAPI - old sun webserver product)
#                         (still applicable)
#    I think so - http://blogs.oracle.com/natarajan/entry/php_plug_in_for_oracle
#                         (now known as Oracle iPlanet Web Server 7)
#
# 5) install_php - this is called AFTER php builds and installs
#          cd $(PHP_DIR); make install
#          cd $(PHP_NSAPI); make libphp5.la install-modules
#	   ./install-php5
#		don't need fix_bin_scripts()
#			[paths already correct and some things don't exist.]
#               looks like i DO NEED the pear patches

COMPONENT_PROJECT_URL=	http://www.php.net/

PKG_PROTO_DIRS += APC/build/prototype/$(MACH)
PKG_PROTO_DIRS += APC-zts/build/prototype/$(MACH)
PKG_PROTO_DIRS += idn/build/prototype/$(MACH)
PKG_PROTO_DIRS += idn-zts/build/prototype/$(MACH)
PKG_PROTO_DIRS += memcache/build/prototype/$(MACH)
PKG_PROTO_DIRS += memcache-zts/build/prototype/$(MACH)
PKG_PROTO_DIRS += php-cgi/build/prototype/$(MACH)
PKG_PROTO_DIRS += php-nsapi/build/prototype/$(MACH)
PKG_PROTO_DIRS += php-sapi/build/prototype/$(MACH)
PKG_PROTO_DIRS += suhosin/build/prototype/$(MACH)
PKG_PROTO_DIRS += suhosin-zts/build/prototype/$(MACH)
PKG_PROTO_DIRS += tcpwrap/build/prototype/$(MACH)
PKG_PROTO_DIRS += tcpwrap-zts/build/prototype/$(MACH)
PKG_PROTO_DIRS += xdebug/build/prototype/$(MACH)
PKG_PROTO_DIRS += xdebug-zts/build/prototype/$(MACH)

# for now, everything with a Makefile should be built
SUBDIRS =	$(shell echo */Makefile | sed -e 's;/Makefile;;g')

.PHONY:	$(SUBDIRS)

download:		TARGET = download
prep:			TARGET = prep
install:		TARGET = install
clean:			TARGET = clean
clobber:		TARGET = clobber
test:			TARGET = test
publish:		TARGET = publish

build:		install

.DEFAULT:	publish

download prep install test publish: $(SUBDIRS)

clean:		$(SUBDIRS)
	$(RM) -r $(BUILD_DIR)

clobber:	$(SUBDIRS) clean

$(SUBDIRS):	FORCE
	@cd $@ && echo "$(TARGET) $@" && $(MAKE) $(TARGET)

# declare module dependencies
APC:		php-sapi
APC-zts:	php-sapi php-nsapi
idn:		php-sapi
idn-zts:	php-sapi php-nsapi
memcache:	php-sapi
memcache-zts:	php-sapi php-nsapi
php-cgi:	php-sapi
php-nsapi:	php-sapi
php-sapi:	imap
suhosin:	php-sapi
suhosin-zts:	php-sapi php-nsapi
tcpwrap:	php-sapi
tcpwrap-zts:	php-sapi php-nsapi
xdebug:		php-sapi
xdebug-zts:	php-sapi php-nsapi

FORCE:
