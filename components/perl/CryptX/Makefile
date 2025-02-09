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
#   $WS_TOOLS/perl-integrate-module CryptX
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		CryptX
HUMAN_VERSION =			0.085
COMPONENT_SUMMARY =		Cryptographic toolkit
COMPONENT_CPAN_AUTHOR =		MIK
COMPONENT_ARCHIVE_HASH =	\
	sha256:be817c6d254c236d2c42958a1bcba4b9dbee1855b7160fa2ecf9cf2934b33ffe
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/json

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/math-bigint
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
