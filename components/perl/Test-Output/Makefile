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
#   $WS_TOOLS/perl-integrate-module Test-Output
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Test-Output
HUMAN_VERSION =			1.035
COMPONENT_SUMMARY =		Utilities to test STDOUT and STDERR messages.
COMPONENT_CPAN_AUTHOR =		BRIANDFOY
COMPONENT_ARCHIVE_HASH =	\
	sha256:be213597f1b878317dd8ab46f308891d9c68ec0df5d729830011c15bbd9e525a
COMPONENT_LICENSE =		Artistic-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod-coverage

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/capture-tiny
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/file-temp
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
