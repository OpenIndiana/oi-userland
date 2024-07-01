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
#   $WS_TOOLS/perl-integrate-module LWP::Protocol::https
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		LWP::Protocol::https
HUMAN_VERSION =			6.14
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		LWP::Protocol::https - Provide https support for LWP::UserAgent
COMPONENT_CPAN_AUTHOR =		OALDERS
COMPONENT_ARCHIVE_HASH =	\
	sha256:59cdeabf26950d4f1bef70f096b0d77c5b1c5a7b5ad1b66d71b681ba279cbb2a
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# remove lines with version numbers
COMPONENT_TEST_TRANSFORMS += '-e "/^    \#/d"'

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/io-socket-ssl
PERL_REQUIRED_PACKAGES += library/perl-5/libwww-perl
PERL_REQUIRED_PACKAGES += library/perl-5/net-http
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/io-socket-ssl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/libwww-perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-needs
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-requiresinternet
