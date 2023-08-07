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
#   $WS_TOOLS/perl-integrate-module Authen::SASL
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Authen::SASL
HUMAN_VERSION =			2.16
COMPONENT_SUMMARY =		Authen::SASL - SASL Authentication framework
COMPONENT_CPAN_AUTHOR =		GBARR
COMPONENT_ARCHIVE_HASH =	\
	sha256:6614fa7518f094f853741b63c73f3627168c5d3aca89b1d02b1016dc32854e09
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Makefile.PL needs to find bundled inc::Module::Install
COMPONENT_CONFIGURE_ENV += PERL5LIB=$(@D)

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/digest-hmac
PERL_REQUIRED_PACKAGES += runtime/perl
