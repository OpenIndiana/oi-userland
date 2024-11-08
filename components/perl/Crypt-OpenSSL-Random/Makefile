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
#   $WS_TOOLS/perl-integrate-module Crypt::OpenSSL::Random
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Crypt::OpenSSL::Random
HUMAN_VERSION =			0.17
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Crypt::OpenSSL::Random - OpenSSL/LibreSSL pseudo-random number generator access
COMPONENT_CPAN_AUTHOR =		RURBAN
COMPONENT_ARCHIVE_HASH =	\
	sha256:a571b24181baaa76c96704e92acffc6934ff593e380dade274db4e43c140ad51
COMPONENT_LICENSE =		Artistic-1.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Set OPENSSL_PREFIX so Crypt::OpenSSL::Guess is able to find our preferred OpenSSL
COMPONENT_CONFIGURE_ENV += OPENSSL_PREFIX=$(OPENSSL_PREFIX)

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/crypt-openssl-guess
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod
