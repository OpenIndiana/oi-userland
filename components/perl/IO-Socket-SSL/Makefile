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
#   $WS_TOOLS/perl-integrate-module IO::Socket::SSL
#

BUILD_STYLE = makemaker
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		IO::Socket::SSL
HUMAN_VERSION =			2.083
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		IO::Socket::SSL - Nearly transparent SSL encapsulation for IO::Socket::INET.
COMPONENT_CPAN_AUTHOR =		SULLR
COMPONENT_ARCHIVE_HASH =	\
	sha256:904ef28765440a97d8a9a0df597f8c3d7f3cb0a053d1b082c10bed03bc802069
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/io-socket-inet6

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/net-ssleay
PERL_REQUIRED_PACKAGES += runtime/perl
