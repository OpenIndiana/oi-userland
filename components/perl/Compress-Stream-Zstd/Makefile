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
#   $WS_TOOLS/perl-integrate-module Compress-Stream-Zstd
#

BUILD_STYLE = modulebuild

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Compress-Stream-Zstd
HUMAN_VERSION =			0.207
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Perl interface to the Zstd (Zstandard) (de)compressor
COMPONENT_CPAN_AUTHOR =		PMQS
COMPONENT_ARCHIVE_HASH =	\
	sha256:85e6a598294ded927b5178ee307e53224373461b9fdceddff7163abca50da3e0
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

# The 0.217 version was briefly available at CPAN and so we packaged it.
# It later disappeared because it was created mistakenly but since IPS cannot
# downgrade we need to keep it.
COMPONENT_VERSION =		0.217

include $(WS_MAKE_RULES)/common.mk

# Build needs GNU make
PATH=$(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/module-build
REQUIRED_PACKAGES.perl += library/perl-5/parent
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
