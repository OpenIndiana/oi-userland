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
#   $WS_TOOLS/perl-integrate-module Math-GMPz
#

BUILD_STYLE = makemaker
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Math-GMPz
HUMAN_VERSION =			0.69
COMPONENT_SUMMARY =		Perl interface to the GMP integer functions
COMPONENT_CPAN_AUTHOR =		SISYPHUS
COMPONENT_ARCHIVE_HASH =	\
	sha256:12a42f5e102fc6af208f7e6d7c28c5214ff6a1656b4b3c4488104017b2c4803c
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-warn
