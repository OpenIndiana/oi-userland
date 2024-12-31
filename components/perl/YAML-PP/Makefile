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
#   $WS_TOOLS/perl-integrate-module YAML-PP
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		YAML-PP
HUMAN_VERSION =			v0.38.0
COMPONENT_SUMMARY =		YAML 1.2 Processor
COMPONENT_CPAN_AUTHOR =		TINITA
COMPONENT_ARCHIVE_HASH =	\
	sha256:a819465c52f6a341049a3942742c08e04f2894b2a66482e43a7f407ce10b4ea0
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# order of these lines changes with every test run
COMPONENT_TEST_TRANSFORMS += '-e "/^YAML::PP::Test/,/}/d"'

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/encode
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/getopt-long
PERL_REQUIRED_PACKAGES += library/perl-5/mime-base64
PERL_REQUIRED_PACKAGES += library/perl-5/module-load
PERL_REQUIRED_PACKAGES += library/perl-5/scalar-list-utils
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-deep
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-warn
