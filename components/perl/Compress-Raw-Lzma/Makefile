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
#   $WS_TOOLS/perl-integrate-module Compress-Raw-Lzma
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Compress-Raw-Lzma
HUMAN_VERSION =			2.214
COMPONENT_SUMMARY =		Low-Level Perl Interface to lzma compression library
COMPONENT_CPAN_AUTHOR =		PMQS
COMPONENT_ARCHIVE_HASH =	\
	sha256:1dcc4448969acad4550376476e3fcd2ed96bfaaae7d9622958fd8f9a1ab4c87d
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += runtime/perl
