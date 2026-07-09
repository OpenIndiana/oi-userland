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
#   $WS_TOOLS/perl-integrate-module DateTime-TimeZone
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		DateTime-TimeZone
HUMAN_VERSION =			2.69
COMPONENT_SUMMARY =		Time zone object base class and factory
COMPONENT_CPAN_AUTHOR =		DROLSKY
COMPONENT_ARCHIVE_HASH =	\
	sha256:a8e285cd14bc7f40daae8028bc912e1d0c53bb9ac464659ad64a36cc5e2bf35f
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# DateTime-TimeZone --> DateTime ==> DateTime-TimeZone
#
# To break loops we need to allow this component to integrate without testing in
# a case the required packages are not available yet (bootstrap).
#
PERL_TEST_BOOTSTRAP = yes

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/datetime

# Auto-generated dependencies
REQUIRED_PACKAGES.perl += library/perl-5/class-singleton
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/module-runtime
REQUIRED_PACKAGES.perl += library/perl-5/namespace-autoclean
REQUIRED_PACKAGES.perl += library/perl-5/params-validationcompiler
REQUIRED_PACKAGES.perl += library/perl-5/parent
REQUIRED_PACKAGES.perl += library/perl-5/scalar-list-utils
REQUIRED_PACKAGES.perl += library/perl-5/specio
REQUIRED_PACKAGES.perl += library/perl-5/try-tiny
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/cpan-meta
TEST_REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
TEST_REQUIRED_PACKAGES.perl += library/perl-5/file-path
TEST_REQUIRED_PACKAGES.perl += library/perl-5/file-temp
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-fatal
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-requires
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
