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
#   $WS_TOOLS/perl-integrate-module Sereal-Encoder
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Sereal-Encoder
HUMAN_VERSION =			5.006
COMPONENT_SUMMARY =		Fast, compact, powerful binary serialization
COMPONENT_CPAN_AUTHOR =		YVES
COMPONENT_ARCHIVE_HASH =	\
	sha256:90b42cc8775982ae0c7499e8f592ce7aefae83433583e10a5ad5712811d170ad
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# To allow unattended installation we need to set few environment variables.
CONFIGURE_ENV += USE_UNALIGNED=no
CONFIGURE_ENV += NO_ASM=no

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/devel-checklib
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/sereal-decoder
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/scalar-list-utils
TEST_REQUIRED_PACKAGES.perl += library/perl-5/sereal-decoder
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-deep
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-differences
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-longstring
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-warn
