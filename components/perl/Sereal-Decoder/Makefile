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
#   $WS_TOOLS/perl-integrate-module Sereal::Decoder
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Sereal::Decoder
HUMAN_VERSION =			5.004
COMPONENT_SUMMARY =		Sereal::Decoder - Fast, compact, powerful binary deserialization
COMPONENT_CPAN_AUTHOR =		YVES
COMPONENT_ARCHIVE_HASH =	\
	sha256:68ef0314d87d1a6e60bb0f66fcf43eb2cacdeb1754432f5e25e784e39d3e6784
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# To allow unattended installation we need to set few environment variables.
COMPONENT_CONFIGURE_ENV += USE_UNALIGNED=no
COMPONENT_CONFIGURE_ENV += NO_ASM=no

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/devel-checklib
PERL_REQUIRED_PACKAGES += library/perl-5/test-deep
PERL_REQUIRED_PACKAGES += library/perl-5/test-differences
PERL_REQUIRED_PACKAGES += library/perl-5/test-longstring
PERL_REQUIRED_PACKAGES += library/perl-5/test-warn
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-deep
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-differences
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-longstring
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-warn
