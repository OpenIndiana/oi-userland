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
#   $WS_TOOLS/perl-integrate-module Math::Random::ISAAC
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Math::Random::ISAAC
HUMAN_VERSION =			1.004
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Math::Random::ISAAC - Perl interface to the ISAAC PRNG algorithm
COMPONENT_CPAN_AUTHOR =		JAWNSY
COMPONENT_ARCHIVE_HASH =	\
	sha256:2773f02fbf207e9745e76a037df08bf5a8cc987ed23c57040ce7f7b1561f2b7c
COMPONENT_LICENSE =		Artistic-2.0 OR GPL-3.0-only
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

#
# There is circular runtime dependency:
#
#	Math-Random-ISAAC recommends Math-Random-ISAAC-XS
#	Math-Random-ISAAC-XS recommends Math-Random-ISAAC
#
# To bootstrap both components we need to build Math-Random-ISAAC first and
# remove any unresolved runtime dependency on Math-Random-ISAAC-XS.
#
MANGLE_DEPEND_RUNTIME += | \
	$(GNU_GREP) -v '^depend type=require fmri=__TBD pkg\.debug\.depend\.file=Math/Random/ISAAC/XS\.pm'

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/math-random-isaac-xs
PERL_REQUIRED_PACKAGES += library/perl-5/test-nowarnings
PERL_REQUIRED_PACKAGES += runtime/perl
