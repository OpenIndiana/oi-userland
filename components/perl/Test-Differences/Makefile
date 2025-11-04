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
#   $WS_TOOLS/perl-integrate-module Test-Differences
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Test-Differences
HUMAN_VERSION =			0.72
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Test strings and data structures and show differences if not ok
COMPONENT_CPAN_AUTHOR =		DCANTRELL
COMPONENT_ARCHIVE_HASH =	\
	sha256:648844b9dcb7dae6f9b5a15c9359d0f09de247a624b65c4620ebff249558f913
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod-coverage

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/capture-tiny
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/test-simple
PERL_REQUIRED_PACKAGES += library/perl-5/text-diff
PERL_REQUIRED_PACKAGES += runtime/perl
