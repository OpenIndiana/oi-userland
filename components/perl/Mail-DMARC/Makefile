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
#   $WS_TOOLS/perl-integrate-module Mail::DMARC
#

BUILD_STYLE = modulebuild

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Mail::DMARC
HUMAN_VERSION =			1.20230215
COMPONENT_SUMMARY =		Mail::DMARC - Perl implementation of DMARC
COMPONENT_CPAN_AUTHOR =		MBRADSHAW
COMPONENT_ARCHIVE_HASH =	\
	sha256:57dcf54759cb92448e56e9141340f61344274c58d9dd65aa90aa9ccf0e7eb903
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

#
# Testing with MySQL requires root account without password.
# To set empty password for root you could run the following command:
#
# 	mysql -u root -e 'SET PASSWORD = ""'
#
COMPONENT_PRE_TEST_ACTION += \
	$(MYSQL_BINDIR)/mysql -u root -e 'CREATE DATABASE dmarc_report' ; \
	$(MYSQL_BINDIR)/mysql -u root dmarc_report < $(SOURCE_DIR)/share/mail_dmarc_schema.mysql ;
COMPONENT_POST_TEST_ACTION += \
	$(MYSQL_BINDIR)/mysql -u root -e 'DROP DATABASE dmarc_report' ;

# PostgreSQL
COMPONENT_PRE_TEST_ACTION += \
	$(PG_BINDIR)/createdb -U postgres dmarc_report ; \
	$(PG_BINDIR)/psql -U postgres dmarc_report < $(SOURCE_DIR)/share/mail_dmarc_schema.pgsql ;
COMPONENT_POST_TEST_ACTION += \
	$(PG_BINDIR)/dropdb -U postgres dmarc_report ;

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/dbd-mysql
TEST_REQUIRED_PACKAGES.perl += library/perl-5/dbd-pg

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/config-tiny
PERL_REQUIRED_PACKAGES += library/perl-5/dbd-sqlite
PERL_REQUIRED_PACKAGES += library/perl-5/dbix-simple
PERL_REQUIRED_PACKAGES += library/perl-5/email-mime
PERL_REQUIRED_PACKAGES += library/perl-5/email-sender
PERL_REQUIRED_PACKAGES += library/perl-5/email-simple
PERL_REQUIRED_PACKAGES += library/perl-5/file-sharedir
PERL_REQUIRED_PACKAGES += library/perl-5/file-sharedir-install
PERL_REQUIRED_PACKAGES += library/perl-5/io-socket-ssl
PERL_REQUIRED_PACKAGES += library/perl-5/mail-dkim
PERL_REQUIRED_PACKAGES += library/perl-5/module-build
PERL_REQUIRED_PACKAGES += library/perl-5/net-dns
PERL_REQUIRED_PACKAGES += library/perl-5/net-idn-encode
PERL_REQUIRED_PACKAGES += library/perl-5/net-imap-simple
PERL_REQUIRED_PACKAGES += library/perl-5/net-ip
PERL_REQUIRED_PACKAGES += library/perl-5/net-smtps
PERL_REQUIRED_PACKAGES += library/perl-5/net-ssleay
PERL_REQUIRED_PACKAGES += library/perl-5/regexp-common
PERL_REQUIRED_PACKAGES += library/perl-5/socket6
PERL_REQUIRED_PACKAGES += library/perl-5/test-file-sharedir
PERL_REQUIRED_PACKAGES += library/perl-5/uri
PERL_REQUIRED_PACKAGES += library/perl-5/xml-libxml
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-exception
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-file-sharedir
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-output
