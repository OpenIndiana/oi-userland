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
#   $WS_TOOLS/perl-integrate-module Type::Tiny
#

BUILD_STYLE = makemaker
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Type::Tiny
HUMAN_VERSION =			2.006000
COMPONENT_SUMMARY =		Type::Tiny - tiny, yet Moo(se)-compatible type constraint
COMPONENT_CPAN_AUTHOR =		TOBYINK
COMPONENT_ARCHIVE_HASH =	\
	sha256:4c685ebbba5145dc02944c305e8e82759811032a55e6da270a751b63b76500ea
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/devel-hide
TEST_REQUIRED_PACKAGES.perl += library/perl-5/namespace-clean
TEST_REQUIRED_PACKAGES.perl += library/perl-5/specio

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/class-xsaccessor
PERL_REQUIRED_PACKAGES += library/perl-5/devel-lexalias
PERL_REQUIRED_PACKAGES += library/perl-5/devel-stacktrace
PERL_REQUIRED_PACKAGES += library/perl-5/exporter-tiny
PERL_REQUIRED_PACKAGES += library/perl-5/ref-util-xs
PERL_REQUIRED_PACKAGES += library/perl-5/regexp-util
PERL_REQUIRED_PACKAGES += library/perl-5/type-tiny-xs
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/moo
TEST_REQUIRED_PACKAGES.perl += library/perl-5/mouse
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-deep
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-memory-cycle
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-warnings
