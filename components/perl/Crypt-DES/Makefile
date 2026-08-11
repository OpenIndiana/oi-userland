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
#   $WS_TOOLS/perl-integrate-module Crypt-DES
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Crypt-DES
HUMAN_VERSION =			2.09
COMPONENT_SUMMARY =		Perl DES encryption module
COMPONENT_CPAN_AUTHOR =		TIMLEGGE
COMPONENT_ARCHIVE_HASH =	\
	sha256:149cdc0a14e944b4cc5eefb7560c78d8cb25254f9f9774547c880355a7e9f40c
COMPONENT_LICENSE =		BSD-like

include $(WS_MAKE_RULES)/common.mk

# remove lines with timing info from test results
COMPONENT_TEST_TRANSFORMS += '-e "/wallclock/d"'

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/crypt-cbc

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += runtime/perl
