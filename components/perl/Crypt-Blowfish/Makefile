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
#   $WS_TOOLS/perl-integrate-module Crypt::Blowfish
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Crypt::Blowfish
HUMAN_VERSION =			2.14
COMPONENT_SUMMARY =		Crypt::Blowfish - Perl Blowfish encryption module
COMPONENT_CPAN_AUTHOR =		DPARIS
COMPONENT_ARCHIVE_HASH =	\
	sha256:46b3431ffb6bf5b9cb359f79565d48407e652ad2b04fdf5ca62a69e7197a67b1
COMPONENT_LICENSE =		BSD-like

include $(WS_MAKE_RULES)/common.mk

# remove lines with timing info from test results
COMPONENT_TEST_TRANSFORMS += '-e "/wallclock/d"'

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
