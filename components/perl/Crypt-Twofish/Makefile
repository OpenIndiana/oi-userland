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
#   $WS_TOOLS/perl-integrate-module Crypt::Twofish
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Crypt::Twofish
HUMAN_VERSION =			2.18
COMPONENT_SUMMARY =		Crypt::Twofish - The Twofish Encryption Algorithm
COMPONENT_CPAN_AUTHOR =		AMS
COMPONENT_ARCHIVE_HASH =	\
	sha256:5881555d6187972a2382aa0d4db2d74c970b06774c621b6ca523739236d2d501
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Remove benchmarks
COMPONENT_TEST_TRANSFORMS += "-e '/^Benchmarks/,\$$d'"

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/crypt-cbc

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
