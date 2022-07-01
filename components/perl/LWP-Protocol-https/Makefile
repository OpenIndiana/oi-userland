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
# Copyright 2022 Marcel Telka
#

BUILD_STYLE = makemaker
BUILD_BITS = 32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		LWP-Protocol-https
COMPONENT_VERSION =		6.10
COMPONENT_FMRI =		library/perl-5/lwp-protocol-https
COMPONENT_SUMMARY =		LWP::Protocol::https - Provide https support for LWP::UserAgent
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/LWP::Protocol::https
COMPONENT_ARCHIVE_HASH =	\
	sha256:cecfc31fe2d4fc854cac47fce13d3a502e8fdfe60c5bc1c09535743185f2a86c
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/O/OA/OALDERS/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

PERL_REQUIRED_PACKAGES += library/perl-5/io-socket-ssl
PERL_REQUIRED_PACKAGES += library/perl-5/libwww-perl
PERL_REQUIRED_PACKAGES += library/perl-5/mozilla-ca
PERL_REQUIRED_PACKAGES += library/perl-5/net-http
PERL_REQUIRED_PACKAGES += library/perl-5/test-requiresinternet

# Auto-generated dependencies
