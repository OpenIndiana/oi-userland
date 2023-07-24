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

COMPONENT_PERL_MODULE =		Mouse
HUMAN_VERSION =			2.5.10
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Mouse - Moose minus the antlers
COMPONENT_CPAN_AUTHOR =		SKAJI
COMPONENT_ARCHIVE_HASH =	\
	sha256:ce8dc23946153a467ff09765167ee2590f5c502120f48a2d9441733f39aa32ee
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_SRC =			$(COMPONENT_NAME)-v$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/http-message

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/module-build
PERL_REQUIRED_PACKAGES += library/perl-5/module-build-xsutil
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-exception
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-fatal
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-leaktrace
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-output
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-requires
TEST_REQUIRED_PACKAGES.perl += library/perl-5/try-tiny
