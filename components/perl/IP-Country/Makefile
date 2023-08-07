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
#   $WS_TOOLS/perl-integrate-module IP::Country
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		IP::Country
HUMAN_VERSION =			2.28
COMPONENT_SUMMARY =		IP::Country - fast lookup of country codes from IP addresses
COMPONENT_CPAN_AUTHOR =		NWETTERS
COMPONENT_ARCHIVE_HASH =	\
	sha256:88db833a5ab22ed06cb53d6f205725e3b5371b254596053738885e91fa105f75
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Remove stats
COMPONENT_TEST_TRANSFORMS += "-e '/random find/d'"

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/geography-countries
PERL_REQUIRED_PACKAGES += runtime/perl
