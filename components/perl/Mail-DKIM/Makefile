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
#   $WS_TOOLS/perl-integrate-module Mail::DKIM
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Mail::DKIM
HUMAN_VERSION =			1.20230630
COMPONENT_SUMMARY =		Mail::DKIM - Signs/verifies Internet mail with DKIM/DomainKey signatures
COMPONENT_CPAN_AUTHOR =		MBRADSHAW
COMPONENT_ARCHIVE_HASH =	\
	sha256:0fa09a93a00f43ac91017a91628265ae7d47deb507e2770532bbb2597550d3d4
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/crypt-openssl-rsa
PERL_REQUIRED_PACKAGES += library/perl-5/cryptx
PERL_REQUIRED_PACKAGES += library/perl-5/mail-authenticationresults
PERL_REQUIRED_PACKAGES += library/perl-5/mailtools
PERL_REQUIRED_PACKAGES += library/perl-5/net-dns
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/net-dns
TEST_REQUIRED_PACKAGES.perl += library/perl-5/net-dns-resolver-mock
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-requiresinternet
TEST_REQUIRED_PACKAGES.perl += library/perl-5/yaml-libyaml
