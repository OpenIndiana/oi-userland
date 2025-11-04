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
#   $WS_TOOLS/perl-integrate-module Crypt-CBC
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Crypt-CBC
HUMAN_VERSION =			3.07
COMPONENT_SUMMARY =		Encrypt Data with Cipher Block Chaining Mode
COMPONENT_CPAN_AUTHOR =		TIMLEGGE
COMPONENT_ARCHIVE_HASH =	\
	sha256:f4ddfb4dd6ac5013df8341bfa734d9c9ee0f10e2e71215ec8fe5bf780b7c9127
COMPONENT_LICENSE =		Artistic-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# Crypt-CBC --> Crypt-Blowfish --> Crypt-CBC
# Crypt-CBC --> Crypt-DES --> Crypt-CBC
#
# To break loops we need to allow this component to integrate without testing in
# a case the required packages are not available yet (bootstrap).
#
PERL_TEST_BOOTSTRAP = yes

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/crypt-blowfish
TEST_REQUIRED_PACKAGES.perl += library/perl-5/crypt-des
TEST_REQUIRED_PACKAGES.perl += library/perl-5/crypt-idea

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/crypt-pbkdf2
PERL_REQUIRED_PACKAGES += library/perl-5/crypt-urandom
PERL_REQUIRED_PACKAGES += library/perl-5/cryptx
PERL_REQUIRED_PACKAGES += library/perl-5/digest-md5
PERL_REQUIRED_PACKAGES += library/perl-5/digest-sha
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
