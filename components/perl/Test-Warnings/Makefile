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
#   $WS_TOOLS/perl-integrate-module Test::Warnings
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Test::Warnings
HUMAN_VERSION =			0.031
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Test::Warnings - Test for warnings and the lack of them
COMPONENT_CPAN_AUTHOR =		ETHER
COMPONENT_ARCHIVE_HASH =	\
	sha256:1e542909fef305e45563e9878ea1c3b0c7cef1b28bb7ae07eba2e1efabec477b
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENCE

include $(WS_MAKE_RULES)/common.mk

# Part of the test output is randomly generated
COMPONENT_TEST_TRANSFORMS += '-e "s/\(Does::Not::Exist::\)[0-9]*/\1RANDOM/"'

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
