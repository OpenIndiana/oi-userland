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

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		IO::Socket::SSL
HUMAN_VERSION =			2.085
COMPONENT_SUMMARY =		IO::Socket::SSL - Nearly transparent SSL encapsulation for IO::Socket::INET.
COMPONENT_CPAN_AUTHOR =		SULLR
COMPONENT_ARCHIVE_HASH =	\
	sha256:95b2f7c0628a7e246a159665fbf0620d0d7835e3a940f22d3fdd47c3aa799c2e
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/io-socket-inet6

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/net-ssleay
PERL_REQUIRED_PACKAGES += runtime/perl
