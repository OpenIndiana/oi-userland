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
#   $WS_TOOLS/perl-integrate-module YAML-PP
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		YAML-PP
HUMAN_VERSION =			v0.40.0
COMPONENT_SUMMARY =		YAML 1.2 Processor
COMPONENT_CPAN_AUTHOR =		TINITA
COMPONENT_ARCHIVE_HASH =	\
	sha256:76c4d28d5c78f0a5cfec631f0032aff1baa68a705f21f6f4bfe70ad83dce2e33
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# order of these lines changes with every test run
COMPONENT_TEST_TRANSFORMS += '-e "/^YAML::PP::Test/,/}/d"'

# Auto-generated dependencies
REQUIRED_PACKAGES.perl += library/perl-5/encode
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/getopt-long
REQUIRED_PACKAGES.perl += library/perl-5/mime-base64
REQUIRED_PACKAGES.perl += library/perl-5/module-load
REQUIRED_PACKAGES.perl += library/perl-5/scalar-list-utils
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-deep
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-warn
