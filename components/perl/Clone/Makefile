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
#   $WS_TOOLS/perl-integrate-module Clone
#

BUILD_STYLE = makemaker
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Clone
HUMAN_VERSION =			0.48
COMPONENT_SUMMARY =		recursively copy Perl datatypes
COMPONENT_CPAN_AUTHOR =		ATOOMIC
COMPONENT_ARCHIVE_HASH =	\
	sha256:321d4cd1078e19519600abd7bda2991b468603c58455479e3d2e25a5acb1911f
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Pointers varies with every run
COMPONENT_TEST_TRANSFORMS += "-e 's/0x[0-9a-f]\{1,\}/POINTER/g'"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/b-cow
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
