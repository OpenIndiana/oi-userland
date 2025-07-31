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
#   $WS_TOOLS/perl-integrate-module Mail-SPF
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Mail-SPF
HUMAN_VERSION =			3.20250505
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		An object-oriented implementation of Sender Policy Framework
COMPONENT_CPAN_AUTHOR =		ADAVIS
COMPONENT_ARCHIVE_HASH =	\
	sha256:9ac60d00b957e849bafe90a8defdeee2e5ffab1c87ac5a4abc452875e9904863
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Both are provided by library/libspf2 package
GENERATE_EXTRA_CMD += | $(GNU_GREP) -v spfd
GENERATE_EXTRA_CMD += | $(GNU_GREP) -v spfquery

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/error
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/getopt-long
PERL_REQUIRED_PACKAGES += library/perl-5/net-dns
PERL_REQUIRED_PACKAGES += library/perl-5/netaddr-ip
PERL_REQUIRED_PACKAGES += library/perl-5/socket
PERL_REQUIRED_PACKAGES += library/perl-5/uri
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/net-dns
TEST_REQUIRED_PACKAGES.perl += library/perl-5/net-dns-resolver-programmable
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
