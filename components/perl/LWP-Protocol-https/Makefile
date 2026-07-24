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
#   $WS_TOOLS/perl-integrate-module LWP-Protocol-https
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		LWP-Protocol-https
HUMAN_VERSION =			6.17
COMPONENT_SUMMARY =		Provide https support for LWP::UserAgent
COMPONENT_CPAN_AUTHOR =		OALDERS
COMPONENT_ARCHIVE_HASH =	\
	sha256:361c7c1eee8cf66812958f975f26ef2e2272a0c6221d2043477cb9c22b8d1c23
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# remove lines with version numbers
COMPONENT_TEST_TRANSFORMS += '-e "/^    \#/d"'

# Auto-generated dependencies
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/io-socket-ssl
REQUIRED_PACKAGES.perl += library/perl-5/libwww-perl
REQUIRED_PACKAGES.perl += library/perl-5/net-http
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/cpan-meta
TEST_REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
TEST_REQUIRED_PACKAGES.perl += library/perl-5/file-temp
TEST_REQUIRED_PACKAGES.perl += library/perl-5/io-socket-ssl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/libwww-perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/socket
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-needs
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
