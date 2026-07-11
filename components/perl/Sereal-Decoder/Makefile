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
#   $WS_TOOLS/perl-integrate-module Sereal-Decoder
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Sereal-Decoder
HUMAN_VERSION =			5.008
COMPONENT_SUMMARY =		Fast, compact, powerful binary deserialization
COMPONENT_CPAN_AUTHOR =		YVES
COMPONENT_ARCHIVE_HASH =	\
	sha256:bc002d405ed18f7a15711918ab766af1e7278576f0661704329205bb9b9a1b3e
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# Sereal-Decoder --> Sereal-Encoder ==> Sereal-Decoder
#
# To break loops we need to allow this component to integrate without testing in
# a case the required packages are not available yet (bootstrap).
#
PERL_TEST_BOOTSTRAP = yes

# To allow unattended installation we need to set few environment variables.
CONFIGURE_ENV += USE_UNALIGNED=no
CONFIGURE_ENV += NO_ASM=no

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/sereal-encoder

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/devel-checklib
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/scalar-list-utils
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-deep
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-differences
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-longstring
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-warn
