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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		wget
COMPONENT_VERSION=	1.18
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b5b55b75726c04c06fe253daec9329a6f1a3c0c1878e3ea76ebfebc139ea9cc1
COMPONENT_ANITYA_ID=	5124

TPNO=			29459

# Enable adiheap and adistack security extensions
ADIHEAP_MODE =	$(ADIHEAP_ENABLE)
ADISTACK_MODE =	$(ADISTACK_ENABLE)

include $(WS_MAKE_RULES)/gnu-component.mk

# Keep just the final test report
COMPONENT_TEST_TRANSFORMS += '-ne "/^PASS/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^FAIL/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^===/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^\# /p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^See/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^Please/p" '

# Enforce openssl (--with-ssl=openssl) instead of default gnutls
# (--with-ssl) as wget doesn't work for secure connections with gnutls. 
# Set PATH to find /usr/perl5/bin/pod2man, so that the man page wget.1
# can be automatically generated
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	--with-ssl=openssl
CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=	PATH="$(PATH):/usr/perl5/bin"

# Wget test suite will skip majority of tests with few Perl modules
# missing on system. By uncommenting following lines it will pass 82
# tests  out of 83 total tests (1 test in which wget tries to output
# to a non-existing device /dev/full fails with wrong error code).
#URI=URI-1.60
#WWW=libwww-perl-5.837
#SOCK=IO-Socket-SSL-2.005
#COMPONENT_TEST_ENV = "http_proxy="
#COMPONENT_TEST_ENV += "https_proxy="
#COMPONENT_TEST_ENV += "ftp_proxy="
#COMPONENT_TEST_ENV += "no_proxy="
#COMPONENT_PRE_TEST_ACTION = ( \
	cd $(COMPONENT_SRC)/tests; \
	wget http://search.cpan.org/CPAN/authors/id/G/GA/GAAS/$(URI).tar.gz; \
	wget http://search.cpan.org/CPAN/authors/id/G/GA/GAAS/$(WWW).tar.gz; \
	wget http://cpan.metacpan.org/authors/id/S/SU/SULLR/$(SOCK).tar.gz; \
	gtar --get $(URI)/URI $(URI)/URI.pm \
	     --strip-components=1 -f $(URI).tar.gz; \
	gtar --get $(WWW)/lib/HTTP $(WWW)/lib/LWP $(WWW)/lib/LWP.pm \
	     --strip-components=2 -f $(WWW).tar.gz; \
	gtar --get $(SOCK)/lib/IO/Socket/SSL $(SOCK)/lib/IO/Socket/SSL.pm \
	     --strip-components=2 -f $(SOCK).tar.gz; )

REQUIRED_PACKAGES += library/libidn
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += text/texinfo
