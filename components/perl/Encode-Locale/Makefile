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
#   $WS_TOOLS/perl-integrate-module Encode::Locale
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Encode::Locale
HUMAN_VERSION =			1.05
COMPONENT_REVISION =		3
COMPONENT_SUMMARY =		Encode::Locale - Determine the locale encoding
COMPONENT_CPAN_AUTHOR =		GAAS
COMPONENT_ARCHIVE_HASH =	\
	sha256:176fa02771f542a4efb1dbc2a4c928e8f4391bf4078473bd6040d8f11adb0ec1
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Normalize out Perl version
COMPONENT_TEST_TRANSFORMS += "-e 's|\(perl5/\)$(shell echo $(PERL_VERSION) | sed -e 's/\./\\\\./')/|\1\$$(PERLVER)/|'"

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
