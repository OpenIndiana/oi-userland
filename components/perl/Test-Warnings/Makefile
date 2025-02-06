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
#   $WS_TOOLS/perl-integrate-module Test-Warnings
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Test-Warnings
HUMAN_VERSION =			0.038
COMPONENT_SUMMARY =		Test for warnings and the lack of them
COMPONENT_CPAN_AUTHOR =		ETHER
COMPONENT_ARCHIVE_HASH =	\
	sha256:3da27e003a3c3cafed3c09b42be05cf9bdbff0bee5c8590a731b02853880a273
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENCE

include $(WS_MAKE_RULES)/common.mk

# Part of the test output is randomly generated
COMPONENT_TEST_TRANSFORMS += '-e "s/\(Does::Not::Exist::\)[0-9]*/\1RANDOM/"'

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/parent
PERL_REQUIRED_PACKAGES += library/perl-5/test-simple
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/cpan-meta
TEST_REQUIRED_PACKAGES.perl += library/perl-5/cpan-meta-check
TEST_REQUIRED_PACKAGES.perl += library/perl-5/cpan-meta-requirements
TEST_REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
TEST_REQUIRED_PACKAGES.perl += library/perl-5/padwalker
TEST_REQUIRED_PACKAGES.perl += library/perl-5/term-ansicolor
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
