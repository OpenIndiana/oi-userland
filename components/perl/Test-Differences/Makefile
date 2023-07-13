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
#   $WS_TOOLS/perl-integrate-module Test::Differences
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Test::Differences
HUMAN_VERSION =			0.70
COMPONENT_SUMMARY =		Test::Differences - Test strings and data structures and show differences if not ok
COMPONENT_CPAN_AUTHOR =		DCANTRELL
COMPONENT_ARCHIVE_HASH =	\
	sha256:bee1b5186aa9ba27fed2bf1b0674520d0bd0cd051d913387f9086c1f94a56854
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod-coverage

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/capture-tiny
PERL_REQUIRED_PACKAGES += library/perl-5/text-diff
PERL_REQUIRED_PACKAGES += runtime/perl
