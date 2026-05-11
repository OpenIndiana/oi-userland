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
#   $WS_TOOLS/perl-integrate-module TOML-Tiny
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		TOML-Tiny
HUMAN_VERSION =			0.21
COMPONENT_SUMMARY =		a minimal, pure perl TOML parser and serializer
COMPONENT_CPAN_AUTHOR =		OALDERS
COMPONENT_ARCHIVE_HASH =	\
	sha256:be79c165c8b5c416faa267a64032945114b51e80727738451ec1586ad4b0d29c
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/toml-parser

# Auto-generated dependencies
REQUIRED_PACKAGES.perl += library/perl-5/datetime-format-iso8601
REQUIRED_PACKAGES.perl += library/perl-5/datetime-format-rfc3339
REQUIRED_PACKAGES.perl += library/perl-5/encode
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/math-bigint
REQUIRED_PACKAGES.perl += library/perl-5/types-serialiser
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/cpan-meta
TEST_REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
TEST_REQUIRED_PACKAGES.perl += library/perl-5/unicode-linebreak
