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
#   $WS_TOOLS/perl-integrate-module Test::Memory::Cycle
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Test::Memory::Cycle
HUMAN_VERSION =			1.06
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Test::Memory::Cycle - Check for memory leaks and circular memory references
COMPONENT_CPAN_AUTHOR =		PETDANCE
COMPONENT_ARCHIVE_HASH =	\
	sha256:9d53ddfdc964cd8454cb0da4c695b6a3ae47b45839291c34cb9d8d1cfaab3202
COMPONENT_LICENSE =		Artistic-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod-coverage

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/devel-cycle
PERL_REQUIRED_PACKAGES += library/perl-5/padwalker
PERL_REQUIRED_PACKAGES += runtime/perl
