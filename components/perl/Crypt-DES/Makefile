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
#   $WS_TOOLS/perl-integrate-module Crypt::DES
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Crypt::DES
HUMAN_VERSION =			2.07
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Crypt::DES - Perl DES encryption module
COMPONENT_CPAN_AUTHOR =		DPARIS
COMPONENT_ARCHIVE_HASH =	\
	sha256:2db1ebb5837b4cb20051c0ee5b733b4453e3137df0a92306034c867621edd7e7
COMPONENT_LICENSE =		BSD-like

include $(WS_MAKE_RULES)/common.mk

# remove lines with timing info from test results
COMPONENT_TEST_TRANSFORMS += '-e "/wallclock/d"'

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/crypt-cbc

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
