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
#   $WS_TOOLS/perl-integrate-module JSON::MaybeXS
#

BUILD_STYLE = makemaker
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		JSON::MaybeXS
HUMAN_VERSION =			1.004005
COMPONENT_SUMMARY =		JSON::MaybeXS - Use Cpanel::JSON::XS with a fallback to JSON::XS and JSON::PP
COMPONENT_CPAN_AUTHOR =		ETHER
COMPONENT_ARCHIVE_HASH =	\
	sha256:f5b6bc19f579e66b7299f8748b8ac3e171936dc4e7fcb72a8a257a9bd482a331
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/cpanel-json-xs
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-needs
