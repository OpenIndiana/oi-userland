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
#   $WS_TOOLS/perl-integrate-module Crypt-Random
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Crypt-Random
HUMAN_VERSION =			1.56
COMPONENT_SUMMARY =		Cryptographically Secure, True Random Number Generator.
COMPONENT_CPAN_AUTHOR =		TIMLEGGE
COMPONENT_ARCHIVE_HASH =	\
	sha256:e1cb37e58f1da29d75b34d8933cf638a10fdf1c58f056d078ef382fc1bbaf4d5
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Drop random stats
COMPONENT_TEST_TRANSFORMS += "-e '/^Quartile distribution/d'"
COMPONENT_TEST_TRANSFORMS += "-e '/that this data is random/d'"

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/class-loader
PERL_REQUIRED_PACKAGES += library/perl-5/crypt-urandom
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/math-pari
PERL_REQUIRED_PACKAGES += library/perl-5/statistics-chisquare
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/statistics-chisquare
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
