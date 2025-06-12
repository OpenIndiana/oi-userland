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
HUMAN_VERSION =			4.69
COMPONENT_SUMMARY =		Handle Common Gateway Interface requests and responses
COMPONENT_CPAN_AUTHOR =		LEEJO
COMPONENT_ARCHIVE_HASH =	\
	sha256:1bde0b1034eaa32a53dab05dd4c2ddefd3504b951daf91b3e317a5bcf100d259
COMPONENT_LICENSE =		Artistic-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# remove timestamp from test results
COMPONENT_TEST_TRANSFORMS += '-e "s/\[[^]]*\] *//g"'

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/encode
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/file-temp
PERL_REQUIRED_PACKAGES += library/perl-5/html-parser
PERL_REQUIRED_PACKAGES += library/perl-5/parent
PERL_REQUIRED_PACKAGES += library/perl-5/uri
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-nowarnings
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-warn
