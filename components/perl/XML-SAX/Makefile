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
#   $WS_TOOLS/perl-integrate-module XML::SAX
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		XML::SAX
HUMAN_VERSION =			1.02
COMPONENT_REVISION =		3
COMPONENT_SUMMARY =		XML::SAX - Simple API for XML
COMPONENT_CPAN_AUTHOR =		GRANTM
COMPONENT_ARCHIVE_HASH =	\
	sha256:4506c387043aa6a77b455f00f57409f3720aa7e553495ab2535263b4ed1ea12a
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# remove line with timing info from test results
COMPONENT_TEST_TRANSFORMS += '-e "/^parsed/d"'

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/xml-namespacesupport
PERL_REQUIRED_PACKAGES += library/perl-5/xml-sax-base
PERL_REQUIRED_PACKAGES += runtime/perl
