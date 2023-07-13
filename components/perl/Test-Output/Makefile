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
#   $WS_TOOLS/perl-integrate-module Test::Output
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Test::Output
HUMAN_VERSION =			1.034
COMPONENT_SUMMARY =		Test::Output - Utilities to test STDOUT and STDERR messages.
COMPONENT_CPAN_AUTHOR =		BDFOY
COMPONENT_ARCHIVE_HASH =	\
	sha256:cd42e2801c0d2b482d18c9fb4b06c757054818bcbb2824e5dfbf33ad7a3d69a0
COMPONENT_LICENSE =		Artistic-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod-coverage

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/capture-tiny
PERL_REQUIRED_PACKAGES += runtime/perl
