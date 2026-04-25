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
#   $WS_TOOLS/perl-integrate-module Crypt-OpenSSL-RSA
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Crypt-OpenSSL-RSA
HUMAN_VERSION =			0.41
COMPONENT_SUMMARY =		RSA encoding and decoding, using the openSSL libraries
COMPONENT_CPAN_AUTHOR =		TIMLEGGE
COMPONENT_ARCHIVE_HASH =	\
	sha256:82fa839897b88e9c245b6265f3be26d3bc879cae4c7a8151fad4a307c3366822
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-2.0-only
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Set OPENSSL_PREFIX so Crypt::OpenSSL::Guess is able to find our preferred OpenSSL
CONFIGURE_ENV += OPENSSL_PREFIX=$(OPENSSL_PREFIX)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/crypt-openssl-bignum
REQUIRED_PACKAGES.perl += library/perl-5/crypt-openssl-guess
REQUIRED_PACKAGES.perl += library/perl-5/crypt-openssl-random
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
