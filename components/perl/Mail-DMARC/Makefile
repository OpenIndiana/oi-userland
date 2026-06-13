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
#   $WS_TOOLS/perl-integrate-module Mail-DMARC
#

BUILD_STYLE = modulebuild

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Mail-DMARC
HUMAN_VERSION =			1.20260612
COMPONENT_SUMMARY =		Perl implementation of DMARC
COMPONENT_CPAN_AUTHOR =		MSIMERSON
COMPONENT_ARCHIVE_HASH =	\
	sha256:2dc54e8c5ab1a549faac100e936a565efdaccd16e806b9013e91382ba976cf42
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# PostgreSQL
COMPONENT_PRE_TEST_ACTION += \
	$(PG_BINDIR)/createdb -U postgres dmarc_report ; \
	$(PG_BINDIR)/psql -U postgres dmarc_report < $(SOURCE_DIR)/share/mail_dmarc_schema.pgsql ;
COMPONENT_POST_TEST_ACTION += \
	$(PG_BINDIR)/dropdb -U postgres dmarc_report ;

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/dbd-pg

# Auto-generated dependencies
REQUIRED_PACKAGES.perl += library/perl-5/config-tiny
REQUIRED_PACKAGES.perl += library/perl-5/dbd-sqlite
REQUIRED_PACKAGES.perl += library/perl-5/dbix-simple
REQUIRED_PACKAGES.perl += library/perl-5/email-mime
REQUIRED_PACKAGES.perl += library/perl-5/email-sender
REQUIRED_PACKAGES.perl += library/perl-5/email-simple
REQUIRED_PACKAGES.perl += library/perl-5/encode
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/file-sharedir
REQUIRED_PACKAGES.perl += library/perl-5/file-sharedir-install
REQUIRED_PACKAGES.perl += library/perl-5/getopt-long
REQUIRED_PACKAGES.perl += library/perl-5/http-tiny
REQUIRED_PACKAGES.perl += library/perl-5/io-compress
REQUIRED_PACKAGES.perl += library/perl-5/io-socket-ssl
REQUIRED_PACKAGES.perl += library/perl-5/mail-dkim
REQUIRED_PACKAGES.perl += library/perl-5/module-build
REQUIRED_PACKAGES.perl += library/perl-5/module-load
REQUIRED_PACKAGES.perl += library/perl-5/net-dns
REQUIRED_PACKAGES.perl += library/perl-5/net-imap-simple
REQUIRED_PACKAGES.perl += library/perl-5/net-ip
REQUIRED_PACKAGES.perl += library/perl-5/net-smtps
REQUIRED_PACKAGES.perl += library/perl-5/net-ssleay
REQUIRED_PACKAGES.perl += library/perl-5/pod-usage
REQUIRED_PACKAGES.perl += library/perl-5/regexp-common
REQUIRED_PACKAGES.perl += library/perl-5/socket
REQUIRED_PACKAGES.perl += library/perl-5/socket6
REQUIRED_PACKAGES.perl += library/perl-5/sys-syslog
REQUIRED_PACKAGES.perl += library/perl-5/test-file-sharedir
REQUIRED_PACKAGES.perl += library/perl-5/uri
REQUIRED_PACKAGES.perl += library/perl-5/xml-libxml
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/net-dns-resolver-mock
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-exception
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-file-sharedir
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-output
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
