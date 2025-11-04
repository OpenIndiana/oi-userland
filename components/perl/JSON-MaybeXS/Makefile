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
#   $WS_TOOLS/perl-integrate-module JSON-MaybeXS
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		JSON-MaybeXS
HUMAN_VERSION =			1.004008
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Use Cpanel::JSON::XS with a fallback to JSON::XS and JSON::PP
COMPONENT_CPAN_AUTHOR =		ETHER
COMPONENT_ARCHIVE_HASH =	\
	sha256:cd3937afa78831f80a2ad5abab6c51b9e82fca4c31e5856ea208d598db5dc867
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/cpanel-json-xs
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/json-pp
PERL_REQUIRED_PACKAGES += library/perl-5/scalar-list-utils
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-needs
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
