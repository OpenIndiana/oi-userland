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

BUILD_BITS = 64
BUILD_STYLE = justmake

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_perl
COMPONENT_VERSION=	2.0.11
COMPONENT_PROJECT_URL=	http://perl.apache.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ca2a9e18cdf90f9c6023e786369d5ba75e8dac292ebfea9900c29bf42dc16f74
#COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)dist/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_URL=	https://archive.apache.org/dist/perl/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/apache

CONFIGURE_DEFAULT_DIRS=no
PERL_VERSION=5.24

include $(WS_MAKE_RULES)/common.mk

APACHE_USR_PREFIX=/usr/apache2/2.4
AP_PERL5LIB=$(APACHE_USR_PREFIX)/lib/perl
AP_PERL5BIN=$(APACHE_USR_PREFIX)/bin
PERLMAN=$(APACHE_USR_PREFIX)/man

COMPONENT_PRE_BUILD_ACTION= ( \
	cd $(@D); $(PERL) Makefile.PL \
	INSTALLDIRS=perl \
	INSTALLSITELIB=$(AP_PERL5LIB) \
	INSTALLARCHLIB=$(AP_PERL5LIB) \
	INSTALLSITEARCH=$(AP_PERL5LIB) \
	INSTALLPRIVLIB=$(AP_PERL5LIB) \
	SITEARCHEXP=$(AP_PERL5LIB) \
	SITELIBEXP=$(AP_PERL5LIB) \
	INSTALLMAN1DIR=$(PERLMAN)/man1 \
	INSTALLMAN3DIR=$(PERLMAN)/man3 \
	INSTALLSCRIPT=$(AP_PERL5BIN) \
	MP_NO_THREADS=1 \
	MP_APXS=$(APACHE_USR_PREFIX)/bin/apxs\
	MP_APR_CONFIG=/usr/apr/bin/$(MACH64)/apr-1-config) 

COMPONENT_TEST_TARGETS=	test

REQUIRED_PACKAGES += library/apr
REQUIRED_PACKAGES += library/apr-util
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += web/server/apache-24
