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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
# Copyright (c) 2022 Tim Mooney.  All rights reserved
#

BUILD_STYLE = makemaker
BUILD_BITS = 32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Net-DNS
COMPONENT_VERSION =		1.15
COMPONENT_FMRI =		library/perl-5/net-dns
COMPONENT_SUMMARY =		Net::DNS - Perl Interface to the Domain Name System
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Net::DNS
COMPONENT_ARCHIVE_HASH =	\
	sha256:1ad46ba6438b846a94b4f50d53ecfda55f504a17e11b94effb087ff9329e61d0
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/N/NL/NLNETLABS/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		MIT

# until all perl modules have been rebuilt with 5.34, each module sets
# this manually, before including common.mk
PERL_VERSIONS = 5.22 5.24 5.34
PERL_64_ONLY_VERSIONS = 5.24 5.34

include $(WS_MAKE_RULES)/common.mk

#
# need different master test results per version
#
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(PERL_VERSION).master

#
# delete any lines up through test_harness
# delete timings
#
COMPONENT_TEST_TRANSFORMS += \
	'-e "1,/test_harness/d"' \
	'-e "s/,  *[0-9]* wallclock.*//"'

REQUIRED_PACKAGES += library/perl-5/digest-hmac

# Auto-generated dependencies
