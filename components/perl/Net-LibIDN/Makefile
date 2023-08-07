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
#   $WS_TOOLS/perl-integrate-module Net::LibIDN
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Net::LibIDN
HUMAN_VERSION =			0.12
COMPONENT_SUMMARY =		Net::LibIDN - Perl bindings for GNU Libidn
COMPONENT_CPAN_AUTHOR =		THOR
COMPONENT_ARCHIVE_HASH =	\
	sha256:2f8acc9442b3866ec7dc63cd449fc693ae3e930d5d3e5e9430fbb6f393bdbb17
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --with-libidn-inc=/usr/include/idn

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += library/libidn
REQUIRED_PACKAGES += system/library
