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
#   $WS_TOOLS/perl-integrate-module Authen-SASL
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Authen-SASL
HUMAN_VERSION =			2.2100
COMPONENT_SUMMARY =		SASL Authentication framework
COMPONENT_CPAN_AUTHOR =		EHUELS
COMPONENT_ARCHIVE_HASH =	\
	sha256:4f0f100aeed34b52977a94b7df973e7f0b8f92d167b09f2b249bab81e8590e57
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# The order and wording of these messages can vary
COMPONENT_TEST_TRANSFORMS += '-e "/^The .*-MD5 SASL mechanism is .*deprecated by RFC/d"'

# Auto-generated dependencies
REQUIRED_PACKAGES.perl += library/perl-5/crypt-urandom
REQUIRED_PACKAGES.perl += library/perl-5/digest-hmac
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/pod-coverage-trustpod
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod-coverage
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
