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
#   $WS_TOOLS/perl-integrate-module Math-Random-ISAAC
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Math-Random-ISAAC
HUMAN_VERSION =			1.004
COMPONENT_REVISION =		3
COMPONENT_SUMMARY =		Perl interface to the ISAAC PRNG algorithm
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
BOOTSTRAP_SKIP_REQUIRED_PACKAGES.perl += library/perl-5/math-random-isaac-xs
MANGLE_DEPEND_RUNTIME += | \
	$(GNU_GREP) -v '^depend type=require fmri=__TBD pkg\.debug\.depend\.file=Math/Random/ISAAC/XS\.pm'

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# Math-Random-ISAAC --> Math-Random-ISAAC-XS ==> Math-Random-ISAAC
#
# To break loops we need to allow this component to integrate without testing in
# a case the required packages are not available yet (bootstrap).
#
PERL_TEST_BOOTSTRAP = yes

# Math-Random-ISAAC-XS is optional dependency to run tests.  It is also
# recommended circular runtime dependency (see above).  In a case we are in
# bootstrap mode the package won't be listed in REQUIRED_PACKAGES and so the
# dependency for running tests won't enforced either.  To solve that we need to
# list Math-Random-ISAAC-XS as a test dependency explicitly.
TEST_REQUIRED_PACKAGES.perl += library/perl-5/math-random-isaac-xs

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-without-module

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/math-random-isaac-xs
PERL_REQUIRED_PACKAGES += library/perl-5/test-nowarnings
PERL_REQUIRED_PACKAGES += library/perl-5/test-simple
PERL_REQUIRED_PACKAGES += runtime/perl
