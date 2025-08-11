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
#   $WS_TOOLS/perl-integrate-module Mail-SpamAssassin
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Mail-SpamAssassin
HUMAN_VERSION =			4.000002
COMPONENT_SUMMARY =		Apache SpamAssassin is an extensible email filter which is used to identify spam
COMPONENT_CPAN_AUTHOR =		GBECHIS
COMPONENT_ARCHIVE_HASH =	\
	sha256:c521be978cef3d49b1e139477ca60a0bd498345fc98274796e44161fae49a17f
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# https://bz.apache.org/SpamAssassin/show_bug.cgi?id=8298
COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)

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
PERL_REQUIRED_PACKAGES += library/perl-5/archive-tar
PERL_REQUIRED_PACKAGES += library/perl-5/archive-zip
PERL_REQUIRED_PACKAGES += library/perl-5/bsd-resource
PERL_REQUIRED_PACKAGES += library/perl-5/db_file
PERL_REQUIRED_PACKAGES += library/perl-5/dbd-sqlite
PERL_REQUIRED_PACKAGES += library/perl-5/dbi
PERL_REQUIRED_PACKAGES += library/perl-5/email-address-xs
PERL_REQUIRED_PACKAGES += library/perl-5/encode-detect
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/geo-ip
PERL_REQUIRED_PACKAGES += library/perl-5/html-parser
PERL_REQUIRED_PACKAGES += library/perl-5/io-compress
PERL_REQUIRED_PACKAGES += library/perl-5/io-socket-ip
PERL_REQUIRED_PACKAGES += library/perl-5/io-socket-ssl
PERL_REQUIRED_PACKAGES += library/perl-5/io-string
PERL_REQUIRED_PACKAGES += library/perl-5/io-zlib
PERL_REQUIRED_PACKAGES += library/perl-5/ip-country
PERL_REQUIRED_PACKAGES += library/perl-5/ip-country-db_file
PERL_REQUIRED_PACKAGES += library/perl-5/libnet
PERL_REQUIRED_PACKAGES += library/perl-5/lwp-protocol-https
PERL_REQUIRED_PACKAGES += library/perl-5/mail-dkim
PERL_REQUIRED_PACKAGES += library/perl-5/mail-dmarc
PERL_REQUIRED_PACKAGES += library/perl-5/mail-spf
PERL_REQUIRED_PACKAGES += library/perl-5/mime-base64
PERL_REQUIRED_PACKAGES += library/perl-5/net-cidr-lite
PERL_REQUIRED_PACKAGES += library/perl-5/net-dns
PERL_REQUIRED_PACKAGES += library/perl-5/net-libidn
PERL_REQUIRED_PACKAGES += library/perl-5/net-libidn2
PERL_REQUIRED_PACKAGES += library/perl-5/net-patricia
PERL_REQUIRED_PACKAGES += library/perl-5/netaddr-ip
PERL_REQUIRED_PACKAGES += library/perl-5/pod-usage
PERL_REQUIRED_PACKAGES += library/perl-5/razor2-client-agent
PERL_REQUIRED_PACKAGES += library/perl-5/time-local
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.perl += library/perl-5/devel-cycle
TEST_REQUIRED_PACKAGES.perl += library/perl-5/net-dns
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
TEST_REQUIRED_PACKAGES.perl += library/perl-5/text-diff
