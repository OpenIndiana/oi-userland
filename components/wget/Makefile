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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		wget
COMPONENT_VERSION=	1.14
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/wget/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1761d7f7c6a2ad6c8d494d239c53f0c17126efb6449ada16dee3a66d87a4147b
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/wget/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/wget

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Enforce openssl (--with-ssl=openssl) instead of default gnutls
# (--with-ssl) as wget doesn't work for secure connections with gnutls. 
# Set PATH to find /usr/perl5/bin/pod2man, so that the man page wget.1
# can be automatically generated
CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--with-ssl=openssl
CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=	PATH="$(PATH):/usr/perl5/bin"

# Wget test suite will skip majority of tests with few Perl modules
# missing on system. By uncommenting following lines it will pass 68
# tests  out of 70 total tests (2 tests are skipped).
#URI=URI-1.60
#WWW=libwww-perl-5.837
#COMPONENT_TEST_ENV = "http_proxy="
#COMPONENT_PRE_TEST_ACTION = ( \
	cd $(COMPONENT_SRC)/tests; \
	wget http://search.cpan.org/CPAN/authors/id/G/GA/GAAS/$(URI).tar.gz; \
	wget http://search.cpan.org/CPAN/authors/id/G/GA/GAAS/$(WWW).tar.gz; \
	gtar --get $(URI)/URI $(URI)/URI.pm \
	     --strip-components=1 -f $(URI).tar.gz; \
	gtar --get $(WWW)/lib/HTTP $(WWW)/lib/LWP $(WWW)/lib/LWP.pm \
	     --strip-components=2 -f $(WWW).tar.gz; )

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
