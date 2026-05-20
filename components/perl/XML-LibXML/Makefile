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
#   $WS_TOOLS/perl-integrate-module XML-LibXML
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		XML-LibXML
HUMAN_VERSION =			2.0212
COMPONENT_SUMMARY =		Interface to Gnome libxml2 xml parsing and DOM library
COMPONENT_CPAN_AUTHOR =		TODDR
COMPONENT_ARCHIVE_HASH =	\
	sha256:c54617078b72e764534beb37e4c452c99cc77aef5c87d2495cb5573a33415bb2
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/alien-build
REQUIRED_PACKAGES.perl += library/perl-5/alien-libxml2
REQUIRED_PACKAGES.perl += library/perl-5/encode
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/parent
REQUIRED_PACKAGES.perl += library/perl-5/scalar-list-utils
REQUIRED_PACKAGES.perl += library/perl-5/xml-namespacesupport
REQUIRED_PACKAGES.perl += library/perl-5/xml-sax
REQUIRED_PACKAGES.perl += library/perl-5/xml-sax-base
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/scalar-list-utils
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
