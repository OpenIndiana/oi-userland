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

COMPONENT_NAME =		Email-Address-XS
HUMAN_VERSION =			1.04
COMPONENT_VERSION =		1.4
COMPONENT_FMRI =		library/perl-5/email-address-xs
COMPONENT_SUMMARY =		Email::Address::XS - Parse and format RFC 5322 email addresses and groups
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Email::Address::XS
COMPONENT_ARCHIVE_HASH =	\
	sha256:995f6d04a7b487dd5e1b55e3b52cad84c87750937c96feb6e24e8f1f10cd593e
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/P/PA/PALI/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
