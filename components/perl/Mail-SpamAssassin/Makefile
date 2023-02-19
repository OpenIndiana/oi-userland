#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# This file was automatically generated using the following command:
#   $WS_TOOLS/perl-integrate-module Mail::SpamAssassin
#

BUILD_STYLE = makemaker
USE_OPENSSL11 = yes


include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Mail::SpamAssassin
HUMAN_VERSION =			4.0.0
COMPONENT_SUMMARY =		Mail::SpamAssassin - Spam detector and markup engine
COMPONENT_CPAN_AUTHOR =		SIDNEY
COMPONENT_ARCHIVE_HASH =	\
	sha256:65979da7d103e3c37563f23a1a24f470090afb33664348968a00bf3d09a84f36
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

LDFLAGS=-L/usr/openssl/1.1/lib/amd64
CFLAGS=-I/usr/openssl/1.1/include
# add CONFIGURE options
CONFIGURE_OPTIONS = INSTALLDIRS=vendor CONTACT_ADDRESS=postmaster@example.com SYSCONFDIR=/etc DATADIR=/usr/share/spamassassin LOCALSTATEDIR=/var/spamassassin ENABLE_SSL=yes < /dev/null
# to force openssl 1.1
COMPONENT_POST_CONFIGURE_ACTION+= $(GSED) -i -e 's:SSLCFLAGS =:SSLCFLAGS = -I/usr/openssl/1.1/include/:' -e 's:SSLLIBS =:SSLLIBS = -L/usr/openssl/1.1/lib/amd64:' $(@D)/spamc/Makefile.in


# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/html-parser
PERL_REQUIRED_PACKAGES += library/perl-5/mail-dkim
PERL_REQUIRED_PACKAGES += library/perl-5/net-dns
PERL_REQUIRED_PACKAGES += library/perl-5/netaddr-ip
PERL_REQUIRED_PACKAGES += library/perl-5/text-diff
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
