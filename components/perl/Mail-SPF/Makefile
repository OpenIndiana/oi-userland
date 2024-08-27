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
#   $WS_TOOLS/perl-integrate-module Mail::SPF
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Mail::SPF
HUMAN_VERSION =			3.20240827
COMPONENT_SUMMARY =		Mail::SPF - An object-oriented implementation of Sender Policy Framework
COMPONENT_CPAN_AUTHOR =		MBRADSHAW
COMPONENT_ARCHIVE_HASH =	\
	sha256:b643b58e73eec3681451a6ffc9f0f95e4dd9a3c6a1af01eb2bd527dab3cfbaa2
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Both are provided by library/libspf2 package
GENERATE_EXTRA_CMD += | $(GNU_GREP) -v spfd
GENERATE_EXTRA_CMD += | $(GNU_GREP) -v spfquery

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/error
PERL_REQUIRED_PACKAGES += library/perl-5/net-dns
PERL_REQUIRED_PACKAGES += library/perl-5/netaddr-ip
PERL_REQUIRED_PACKAGES += library/perl-5/uri
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/net-dns
TEST_REQUIRED_PACKAGES.perl += library/perl-5/net-dns-resolver-programmable
