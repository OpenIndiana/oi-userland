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
USE_COMMON_TEST_MASTER = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		MIME-Lite
HUMAN_VERSION =			3.033
COMPONENT_VERSION =		3.33
COMPONENT_FMRI =		library/perl-5/mime-lite
COMPONENT_SUMMARY =		MIME::Lite - low-calorie MIME generator
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/MIME::Lite
COMPONENT_ARCHIVE_HASH =	\
	sha256:78a279f1d2e242551c347ef97a13fc675766602cb84c2a80c569400f4f368bab
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/R/RJ/RJBS/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

PERL_REQUIRED_PACKAGES += library/perl-5/email-date-format
PERL_REQUIRED_PACKAGES += library/perl-5/mailtools
PERL_REQUIRED_PACKAGES += library/perl-5/mime-types

# Auto-generated dependencies
