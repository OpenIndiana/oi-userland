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
#   $WS_TOOLS/perl-integrate-module Tie::EncryptedHash
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Tie::EncryptedHash
HUMAN_VERSION =			1.24
COMPONENT_SUMMARY =		Tie::EncryptedHash - Hashes (and objects based on hashes) with encrypting fields.
COMPONENT_CPAN_AUTHOR =		VIPUL
COMPONENT_ARCHIVE_HASH =	\
	sha256:aa9a083a231e4046170a5894644e3c59679c7dbd0aa2d1217dc85150df2c1e21
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Remove deprecation warnings
COMPONENT_TEST_TRANSFORMS += "-e '/WARNING:.*opensslv1.*deprecated.*pbkdf2/d'"
COMPONENT_TEST_TRANSFORMS += "-e '/Pass -nodeprecate=>1 to inhibit this message./d'"
COMPONENT_TEST_TRANSFORMS += "-e '\|lib/Tie/EncryptedHash\.pm line 125\.|d'"

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/crypt-blowfish
PERL_REQUIRED_PACKAGES += library/perl-5/crypt-cbc
PERL_REQUIRED_PACKAGES += library/perl-5/crypt-des
PERL_REQUIRED_PACKAGES += runtime/perl
