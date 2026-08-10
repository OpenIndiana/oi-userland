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
#   $WS_TOOLS/perl-integrate-module Math-Prime-Util-GMP
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Math-Prime-Util-GMP
HUMAN_VERSION =			0.54
COMPONENT_SUMMARY =		Utilities related to prime numbers, using GMP
COMPONENT_CPAN_AUTHOR =		DANAJ
COMPONENT_ARCHIVE_HASH =	\
	sha256:5ad4be0f8d349432fbe10df67bc3a82b4bc4b0bade2a13e2c8a35b7fb9ddfd1f
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

#
# There is circular runtime dependency:
#
#	Math-Prime-Util-GMP recommends Math-Prime-Util
#	Math-Prime-Util requires Math-Prime-Util-GMP
#
# To bootstrap both components we need to build Math-Prime-Util-GMP first and remove any
# unresolved runtime dependency on Math-Prime-Util.
#
BOOTSTRAP_SKIP_REQUIRED_PACKAGES.perl += library/perl-5/math-prime-util
MANGLE_DEPEND_RUNTIME += | \
	$(GNU_GREP) -v '^depend type=require fmri=__TBD pkg\.debug\.depend\.file=Math/Prime/Util\.pm'

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/math-prime-util
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/math-bigint
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
