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
#   $WS_TOOLS/perl-integrate-module CGI
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		CGI
HUMAN_VERSION =			4.72
COMPONENT_SUMMARY =		Handle Common Gateway Interface requests and responses
COMPONENT_CPAN_AUTHOR =		LEEJO
COMPONENT_ARCHIVE_HASH =	\
	sha256:babc1ca72db188083a1c3812debe88c4473b943b1f7c662281cd57c580a8bdd9
COMPONENT_LICENSE =		Artistic-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# remove timestamp from test results
COMPONENT_TEST_TRANSFORMS += '-e "s/\[[^]]*\] *//g"'

# Auto-generated dependencies
REQUIRED_PACKAGES.perl += library/perl-5/encode
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/file-temp
REQUIRED_PACKAGES.perl += library/perl-5/html-parser
REQUIRED_PACKAGES.perl += library/perl-5/parent
REQUIRED_PACKAGES.perl += library/perl-5/uri
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-nowarnings
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-warn
