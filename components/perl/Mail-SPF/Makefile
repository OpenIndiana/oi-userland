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

BUILD_STYLE = modulebuild

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Mail::SPF
HUMAN_VERSION =			2.9.0
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Mail::SPF - An object-oriented implementation of Sender Policy Framework
COMPONENT_ARCHIVE_URL=		https://cpan.metacpan.org/authors/id/J/JM/JMEHNLE/mail-spf/Mail-SPF-v2.9.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:61cb5915f1c7acc7a931ffc1bfc1291bdfac555e2a46eb2391b995ea9ecb6162
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_SRC =                 $(COMPONENT_NAME)-v$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

GENERATE_EXTRA_CMD += | $(GNU_GREP) -v spfd
GENERATE_EXTRA_CMD += | $(GNU_GREP) -v spfquery

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/error
PERL_REQUIRED_PACKAGES += library/perl-5/module-build
PERL_REQUIRED_PACKAGES += library/perl-5/net-dns
PERL_REQUIRED_PACKAGES += library/perl-5/net-dns-resolver-programmable
PERL_REQUIRED_PACKAGES += library/perl-5/netaddr-ip
PERL_REQUIRED_PACKAGES += library/perl-5/uri
PERL_REQUIRED_PACKAGES += runtime/perl
