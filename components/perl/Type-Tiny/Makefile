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
HUMAN_VERSION =			2.008000
COMPONENT_SUMMARY =		tiny, yet Moo(se)-compatible type constraint
COMPONENT_CPAN_AUTHOR =		TOBYINK
COMPONENT_ARCHIVE_HASH =	\
	sha256:997ea06f1c6b9be37c3456294bdf861e632538c29313cd6869ff2b1b1c44dcb3
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/devel-hide
TEST_REQUIRED_PACKAGES.perl += library/perl-5/namespace-clean
TEST_REQUIRED_PACKAGES.perl += library/perl-5/specio

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/class-xsaccessor
PERL_REQUIRED_PACKAGES += library/perl-5/cpan-meta-requirements
PERL_REQUIRED_PACKAGES += library/perl-5/devel-lexalias
PERL_REQUIRED_PACKAGES += library/perl-5/devel-stacktrace
PERL_REQUIRED_PACKAGES += library/perl-5/exporter-tiny
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/ref-util-xs
PERL_REQUIRED_PACKAGES += library/perl-5/regexp-util
PERL_REQUIRED_PACKAGES += library/perl-5/scalar-list-utils
PERL_REQUIRED_PACKAGES += library/perl-5/type-tiny-xs
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/moo
TEST_REQUIRED_PACKAGES.perl += library/perl-5/mouse
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-deep
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-memory-cycle
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-warnings
