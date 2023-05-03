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

COMPONENT_PERL_MODULE =		CGI
HUMAN_VERSION =			4.57
COMPONENT_SUMMARY =		CGI - Handle Common Gateway Interface requests and responses
COMPONENT_CPAN_AUTHOR =		LEEJO
COMPONENT_ARCHIVE_HASH =	\
	sha256:4e6ca634fe0d5621bb55b0fce5c1d08e6f643c65eecdfffbb4b344fd51b963ac
COMPONENT_LICENSE =		Artistic-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# remove timestamp from test results
COMPONENT_TEST_TRANSFORMS += '-e "s/\[[^]]*\] *//g"'

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/html-parser
PERL_REQUIRED_PACKAGES += library/perl-5/test-nowarnings
PERL_REQUIRED_PACKAGES += library/perl-5/test-warn
PERL_REQUIRED_PACKAGES += runtime/perl
