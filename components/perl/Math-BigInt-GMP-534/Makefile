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
#   $WS_TOOLS/perl-integrate-module Math::BigInt::GMP
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Math::BigInt::GMP
HUMAN_VERSION =			1.6007
COMPONENT_SUMMARY =		Math::BigInt::GMP - backend library for Math::BigInt etc. based on GMP
COMPONENT_CPAN_AUTHOR =		PJACKLAM
COMPONENT_ARCHIVE_HASH =	\
	sha256:5d725e6d20ccb37e072673628f0b0dd10e5dd011619f70f50ad58aded454c01f
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

# Math::BigInt::GMP >= 1.6008 requires Math::BigInt >= 1.999819
# Perl 5.34 comes with Math::BigInt 1.999818
# Perl 5.36 comes with Math::BigInt 1.999830
# Perl 5.38 comes with Math::BigInt 1.999837
PERL_VERSIONS = 5.34

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += system/library
