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
#   $WS_TOOLS/perl-integrate-module TOML-Parser
#

BUILD_STYLE = modulebuild

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		TOML-Parser
HUMAN_VERSION =			0.91
COMPONENT_SUMMARY =		simple toml parser
COMPONENT_CPAN_AUTHOR =		KARUPA
COMPONENT_ARCHIVE_HASH =	\
	sha256:2a8513b904e377e0cae726910be676f4ff96bd960001c358dd66dc7c37aa9a8e
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/encode
PERL_REQUIRED_PACKAGES += library/perl-5/module-build-tiny
PERL_REQUIRED_PACKAGES += library/perl-5/parent
PERL_REQUIRED_PACKAGES += library/perl-5/types-serialiser
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/mime-base64
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-deep
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-deep-fuzzy
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
