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
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Authen-SASL
HUMAN_VERSION =			2.1900
COMPONENT_SUMMARY =		SASL Authentication framework
COMPONENT_CPAN_AUTHOR =		EHUELS
COMPONENT_ARCHIVE_HASH =	\
	sha256:be3533a6891b2e677150b479c1a0d4bf11c8bbeebed3e7b8eba34053e93923b0
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/crypt-urandom
PERL_REQUIRED_PACKAGES += library/perl-5/digest-hmac
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/pod-coverage-trustpod
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod-coverage
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
