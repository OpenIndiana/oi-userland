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
#   $WS_TOOLS/perl-integrate-module Type-Tiny
#

BUILD_STYLE = makemaker
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Type-Tiny
HUMAN_VERSION =			2.008005
COMPONENT_SUMMARY =		tiny, yet Moo(se)-compatible type constraint
COMPONENT_CPAN_AUTHOR =		TOBYINK
COMPONENT_ARCHIVE_HASH =	\
	sha256:ec8ebbf710d1b76efee7fd3b3d9fc6f242f7632a4a5020e54a39d95cb18ea94e
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
# https://github.com/tobyink/p5-type-tiny/issues/171
TEST_REQUIRED_PACKAGES.perl += library/perl-5/devel-hide
TEST_REQUIRED_PACKAGES.perl += library/perl-5/namespace-clean
TEST_REQUIRED_PACKAGES.perl += library/perl-5/specio

# Auto-generated dependencies
REQUIRED_PACKAGES.perl += library/perl-5/class-xsaccessor
REQUIRED_PACKAGES.perl += library/perl-5/cpan-meta-requirements
REQUIRED_PACKAGES.perl += library/perl-5/devel-lexalias
REQUIRED_PACKAGES.perl += library/perl-5/devel-stacktrace
REQUIRED_PACKAGES.perl += library/perl-5/exporter-tiny
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/ref-util-xs
REQUIRED_PACKAGES.perl += library/perl-5/regexp-util
REQUIRED_PACKAGES.perl += library/perl-5/scalar-list-utils
REQUIRED_PACKAGES.perl += library/perl-5/type-tiny-xs
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/moo
TEST_REQUIRED_PACKAGES.perl += library/perl-5/mouse
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-deep
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-memory-cycle
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-warnings
