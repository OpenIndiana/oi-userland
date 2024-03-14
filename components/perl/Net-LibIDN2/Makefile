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
#   $WS_TOOLS/perl-integrate-module Net::LibIDN2
#

BUILD_STYLE = modulebuild

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Net::LibIDN2
HUMAN_VERSION =			1.02
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Net::LibIDN2 - Perl bindings for GNU Libidn2
COMPONENT_CPAN_AUTHOR =		THOR
COMPONENT_ARCHIVE_HASH =	\
	sha256:d1f30afc6acfa6541b00c09a7e4c74e7d8e4ba49e3277c0bbc41ae35c1390d07
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# add include path
COMPONENT_CONFIGURE_ARGS = --extra_compiler_flags=-I/usr/include/idn2 --installdirs=vendor

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += library/libidn2
REQUIRED_PACKAGES += system/library
