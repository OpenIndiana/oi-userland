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
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE=		justmake

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_perl
COMPONENT_VERSION=	2.0.13
COMPONENT_PROJECT_URL=	https://perl.apache.org/
COMPONENT_SUMMARY=	Perl plugin for Apache Web Server V2.4
COMPONENT_CLASSIFICATION=Web Services/Application and Web Servers
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:ade3be31c447b8448869fecdfcace258d6d587b8c6c773c5f22735f70d82d6da
COMPONENT_ARCHIVE_URL=	https://archive.apache.org/dist/perl/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/apache
COMPONENT_FMRI=		web/server/apache-24/module/apache-perl
COMPONENT_LICENSE=	Apache v2.0
COMPONENT_LICENSE_FILE=	LICENSE

CONFIGURE_DEFAULT_DIRS=	yes

include $(WS_MAKE_RULES)/common.mk

APACHE_USR_PREFIX=	/usr/apache2/2.4
AP_PERL5LIB=		$(APACHE_USR_PREFIX)/lib/perl
AP_PERL5BIN=		$(APACHE_USR_PREFIX)/bin
PERLMAN=		$(APACHE_USR_PREFIX)/man

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
	LINKTYPE=dynamic \
	MP_APXS=$(APACHE_USR_PREFIX)/bin/apxs \
	MP_APR_CONFIG=/usr/apr/bin/$(MACH64)/apr-1-config)

COMPONENT_TEST_TARGETS=	test

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += library/apr
REQUIRED_PACKAGES += library/apr-util
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/server/apache-24
