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
HUMAN_VERSION =			2.64
COMPONENT_SUMMARY =		Time zone object base class and factory
COMPONENT_CPAN_AUTHOR =		DROLSKY
COMPONENT_ARCHIVE_HASH =	\
	sha256:7c2d638a52e5b5ca77f325e48087495a65ba6bfbd39d858aeba98d21216964cd
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
PERL_REQUIRED_PACKAGES += library/perl-5/class-singleton
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/module-runtime
PERL_REQUIRED_PACKAGES += library/perl-5/namespace-autoclean
PERL_REQUIRED_PACKAGES += library/perl-5/params-validationcompiler
PERL_REQUIRED_PACKAGES += library/perl-5/parent
PERL_REQUIRED_PACKAGES += library/perl-5/scalar-list-utils
PERL_REQUIRED_PACKAGES += library/perl-5/specio
PERL_REQUIRED_PACKAGES += library/perl-5/try-tiny
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/cpan-meta
TEST_REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
TEST_REQUIRED_PACKAGES.perl += library/perl-5/file-path
TEST_REQUIRED_PACKAGES.perl += library/perl-5/file-temp
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-fatal
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-requires
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
