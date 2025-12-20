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
#   $WS_TOOLS/perl-integrate-module Mouse
#

BUILD_STYLE = modulebuild

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Mouse
HUMAN_VERSION =			v2.6.1
COMPONENT_SUMMARY =		Moose minus the antlers
COMPONENT_CPAN_AUTHOR =		SKAJI
COMPONENT_ARCHIVE_HASH =	\
	sha256:aacfba1bfc6f9f89d8ecb26dab8694f256afe44eb675068318759698bb47e29a
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/http-message

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/module-build
REQUIRED_PACKAGES.perl += library/perl-5/module-build-xsutil
REQUIRED_PACKAGES.perl += library/perl-5/scalar-list-utils
REQUIRED_PACKAGES.perl += library/perl-5/version
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-exception
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-fatal
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-leaktrace
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-output
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-requires
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
TEST_REQUIRED_PACKAGES.perl += library/perl-5/try-tiny
