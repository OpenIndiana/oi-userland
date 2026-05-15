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
#   $WS_TOOLS/perl-integrate-module libwww-perl
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		libwww-perl
HUMAN_VERSION =			6.83
COMPONENT_SUMMARY =		The World-Wide Web library for Perl
COMPONENT_CPAN_AUTHOR =		OALDERS
COMPONENT_ARCHIVE_HASH =	\
	sha256:e75f0fa9d3c6f0daf5a5a72fa9f8b1c9c0d23e3a84a8522ccb4f835232b95505
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# libwww-perl --> LWP-Protocol-https ==> libwww-perl
#
# To break loops we need to allow this component to integrate without testing in
# a case the required packages are not available yet (bootstrap).
#
PERL_TEST_BOOTSTRAP = yes

# Auto-generated dependencies
REQUIRED_PACKAGES.perl += library/perl-5/digest-md5
REQUIRED_PACKAGES.perl += library/perl-5/encode
REQUIRED_PACKAGES.perl += library/perl-5/encode-locale
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/file-listing
REQUIRED_PACKAGES.perl += library/perl-5/file-temp
REQUIRED_PACKAGES.perl += library/perl-5/getopt-long
REQUIRED_PACKAGES.perl += library/perl-5/html-parser
REQUIRED_PACKAGES.perl += library/perl-5/http-cookies
REQUIRED_PACKAGES.perl += library/perl-5/http-date
REQUIRED_PACKAGES.perl += library/perl-5/http-message
REQUIRED_PACKAGES.perl += library/perl-5/http-negotiate
REQUIRED_PACKAGES.perl += library/perl-5/libnet
REQUIRED_PACKAGES.perl += library/perl-5/lwp-mediatypes
REQUIRED_PACKAGES.perl += library/perl-5/mime-base64
REQUIRED_PACKAGES.perl += library/perl-5/module-load
REQUIRED_PACKAGES.perl += library/perl-5/net-http
REQUIRED_PACKAGES.perl += library/perl-5/parent
REQUIRED_PACKAGES.perl += library/perl-5/scalar-list-utils
REQUIRED_PACKAGES.perl += library/perl-5/try-tiny
REQUIRED_PACKAGES.perl += library/perl-5/uri
REQUIRED_PACKAGES.perl += library/perl-5/www-robotrules
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/cpan-meta
TEST_REQUIRED_PACKAGES.perl += library/perl-5/data-dump
TEST_REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
TEST_REQUIRED_PACKAGES.perl += library/perl-5/http-cookiejar
TEST_REQUIRED_PACKAGES.perl += library/perl-5/http-daemon
TEST_REQUIRED_PACKAGES.perl += library/perl-5/lwp-protocol-https
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-fatal
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-leaktrace
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-needs
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-requiresinternet
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
