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
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Test::Differences
HUMAN_VERSION =			0.71
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Test::Differences - Test strings and data structures and show differences if not ok
COMPONENT_CPAN_AUTHOR =		DCANTRELL
COMPONENT_ARCHIVE_HASH =	\
	sha256:cac16a56cd843b0809e5b49199d60d75a8dbad7ca9a08380dbf3f5cc3aaa38d9
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod-coverage

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/capture-tiny
PERL_REQUIRED_PACKAGES += library/perl-5/text-diff
PERL_REQUIRED_PACKAGES += runtime/perl
