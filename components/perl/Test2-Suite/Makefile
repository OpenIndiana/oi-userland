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
#   $WS_TOOLS/perl-integrate-module Test2::Suite
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Test2::Suite
HUMAN_VERSION =			0.000163
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Test2::Suite - Distribution with a rich set of tools built upon the Test2 framework.
COMPONENT_CPAN_AUTHOR =		EXODIST
COMPONENT_ARCHIVE_HASH =	\
	sha256:e336c2d92d43c4f0068aa0d67019d56723ab82471e1bd9028300bb6a1602c0a9
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

# Test2::Suite has been added to Perl 5.40 core
PERL_VERSIONS := $(filter 5.36 5.38, $(PERL_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/json-maybexs

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/term-table
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/module-pluggable
TEST_REQUIRED_PACKAGES.perl += library/perl-5/term-size-any
TEST_REQUIRED_PACKAGES.perl += library/perl-5/termreadkey
TEST_REQUIRED_PACKAGES.perl += library/perl-5/unicode-linebreak
