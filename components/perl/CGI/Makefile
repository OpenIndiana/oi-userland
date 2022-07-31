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
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		CGI
HUMAN_VERSION =			4.54
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		CGI - Handle Common Gateway Interface requests and responses
COMPONENT_CPAN_AUTHOR =		LEEJO
COMPONENT_ARCHIVE_HASH =	\
	sha256:9608a044ae2e87cefae8e69b113e3828552ddaba0d596a02f9954c6ac17fa294
COMPONENT_LICENSE =		Artistic-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# remove timestamp from test results
COMPONENT_TEST_TRANSFORMS += '-e "s/\[[^]]*\] *//g"'

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/html-parser
PERL_REQUIRED_PACKAGES += library/perl-5/test-deep
PERL_REQUIRED_PACKAGES += library/perl-5/test-nowarnings
PERL_REQUIRED_PACKAGES += library/perl-5/test-warn
PERL_REQUIRED_PACKAGES += runtime/perl
