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
HUMAN_VERSION =			1.7001
COMPONENT_SUMMARY =		Math::BigInt::GMP - backend library for Math::BigInt etc. based on GMP
COMPONENT_CPAN_AUTHOR =		PJACKLAM
COMPONENT_ARCHIVE_HASH =	\
	sha256:417581fdce63892e24f08279cdd6b065cb60c41d5acfa22dd2ad93b6d3e87071
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

# Math::BigInt::GMP >= 1.6012 requires Math::BigInt >= 1.999838
# Perl 5.36 comes with Math::BigInt 1.999830
# Perl 5.38 comes with Math::BigInt 1.999837
# Perl 5.40 comes with Math::BigInt 2.003002
PERL_VERSIONS := $(filter-out 5.36 5.38, $(PERL_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += system/library
