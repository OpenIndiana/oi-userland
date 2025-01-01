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
#   $WS_TOOLS/perl-integrate-module Test-Simple
#

BUILD_STYLE = makemaker
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Test-Simple
HUMAN_VERSION =			1.302207
COMPONENT_SUMMARY =		Basic utilities for writing tests.
COMPONENT_CPAN_AUTHOR =		EXODIST
COMPONENT_ARCHIVE_HASH =	\
	sha256:5ce22181e77859db99ef4abb4019e5949cb8829d6ef61b62ae8834234c589807
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/json-maybexs

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/file-temp
PERL_REQUIRED_PACKAGES += library/perl-5/scalar-list-utils
PERL_REQUIRED_PACKAGES += library/perl-5/term-table
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/module-pluggable
TEST_REQUIRED_PACKAGES.perl += library/perl-5/term-size-any
TEST_REQUIRED_PACKAGES.perl += library/perl-5/termreadkey
TEST_REQUIRED_PACKAGES.perl += library/perl-5/unicode-linebreak
