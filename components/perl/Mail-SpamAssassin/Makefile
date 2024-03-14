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
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Mail::SpamAssassin
HUMAN_VERSION =			4.0.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Mail::SpamAssassin - Spam detector and markup engine
COMPONENT_CPAN_AUTHOR =		SIDNEY
COMPONENT_ARCHIVE_HASH =	\
	sha256:65979da7d103e3c37563f23a1a24f470090afb33664348968a00bf3d09a84f36
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# see the PACKAGING file
CONFIGURE_OPTIONS += INSTALLDIRS=vendor
CONFIGURE_OPTIONS += CONTACT_ADDRESS=postmaster@example.com
CONFIGURE_OPTIONS += SYSCONFDIR=/etc
CONFIGURE_OPTIONS += DATADIR=/usr/share/spamassassin
CONFIGURE_OPTIONS += LOCALSTATEDIR=/var/spamassassin
CONFIGURE_OPTIONS += ENABLE_SSL=yes
CONFIGURE_OPTIONS += CONFIGURE="\$$(PERL_BIN) spamc/configure.pl LDFLAGS=-L$(OPENSSL_LIBDIR) CFLAGS=-I$(OPENSSL_INCDIR)"
CONFIGURE_OPTIONS += < /dev/null

# install spamassassin
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTO_DIR)/lib/svc/method ; \
	$(CP) $(COMPONENT_DIR)/files/spamassassin $(PROTO_DIR)/lib/svc/method ;
# install spamassassin.xml
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTO_DIR)/lib/svc/manifest/network ; \
	$(CP) $(COMPONENT_DIR)/files/spamassassin.xml $(PROTO_DIR)/lib/svc/manifest/network ;

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/archive-zip
PERL_REQUIRED_PACKAGES += library/perl-5/bsd-resource
PERL_REQUIRED_PACKAGES += library/perl-5/dbd-sqlite
PERL_REQUIRED_PACKAGES += library/perl-5/dbi
PERL_REQUIRED_PACKAGES += library/perl-5/email-address-xs
PERL_REQUIRED_PACKAGES += library/perl-5/encode-detect
PERL_REQUIRED_PACKAGES += library/perl-5/geo-ip
PERL_REQUIRED_PACKAGES += library/perl-5/html-parser
PERL_REQUIRED_PACKAGES += library/perl-5/io-socket-inet6
PERL_REQUIRED_PACKAGES += library/perl-5/io-socket-ssl
PERL_REQUIRED_PACKAGES += library/perl-5/io-string
PERL_REQUIRED_PACKAGES += library/perl-5/ip-country
PERL_REQUIRED_PACKAGES += library/perl-5/ip-country-db_file
PERL_REQUIRED_PACKAGES += library/perl-5/libwww-perl
PERL_REQUIRED_PACKAGES += library/perl-5/mail-dkim
PERL_REQUIRED_PACKAGES += library/perl-5/mail-dmarc
PERL_REQUIRED_PACKAGES += library/perl-5/mail-spf
PERL_REQUIRED_PACKAGES += library/perl-5/net-cidr-lite
PERL_REQUIRED_PACKAGES += library/perl-5/net-dns
PERL_REQUIRED_PACKAGES += library/perl-5/net-libidn
PERL_REQUIRED_PACKAGES += library/perl-5/net-libidn2
PERL_REQUIRED_PACKAGES += library/perl-5/net-patricia
PERL_REQUIRED_PACKAGES += library/perl-5/netaddr-ip
PERL_REQUIRED_PACKAGES += library/perl-5/razor2-client-agent
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.perl += library/perl-5/devel-cycle
TEST_REQUIRED_PACKAGES.perl += library/perl-5/net-dns
TEST_REQUIRED_PACKAGES.perl += library/perl-5/perl-critic
TEST_REQUIRED_PACKAGES.perl += library/perl-5/perl-critic-policy-perlsecret
TEST_REQUIRED_PACKAGES.perl += library/perl-5/text-diff
