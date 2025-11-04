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
#   $WS_TOOLS/perl-integrate-module HTTP-CookieJar
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		HTTP-CookieJar
HUMAN_VERSION =			0.014
COMPONENT_REVISION =		3
COMPONENT_SUMMARY =		A minimalist HTTP user agent cookie jar
COMPONENT_CPAN_AUTHOR =		DAGOLDEN
COMPONENT_ARCHIVE_HASH =	\
	sha256:7094ea5c91f536d263b85e83ab4e9a963e11c4408ce08ecae553fa9c0cc47e73
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/http-message

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/http-date
PERL_REQUIRED_PACKAGES += library/perl-5/mozilla-publicsuffix
PERL_REQUIRED_PACKAGES += library/perl-5/parent
PERL_REQUIRED_PACKAGES += library/perl-5/time-local
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/cpan-meta
TEST_REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-deep
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-requires
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
TEST_REQUIRED_PACKAGES.perl += library/perl-5/time-local
TEST_REQUIRED_PACKAGES.perl += library/perl-5/uri
