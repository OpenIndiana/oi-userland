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
#   $WS_TOOLS/perl-integrate-module NetAddr::IP
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		NetAddr::IP
HUMAN_VERSION =			4.079
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		NetAddr::IP - Manages IPv4 and IPv6 addresses and subnets
COMPONENT_CPAN_AUTHOR =		MIKER
COMPONENT_ARCHIVE_HASH =	\
	sha256:ec5a82dfb7028bcd28bb3d569f95d87dd4166cc19867f2184ed3a59f6d6ca0e7
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-2.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/socket6

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
