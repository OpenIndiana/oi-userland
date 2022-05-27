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

COMPONENT_NAME =		Email-Address
COMPONENT_VERSION =		1.912
COMPONENT_FMRI =		library/perl-5/email-address
COMPONENT_SUMMARY =		Email::Address - RFC 2822 Address Parsing and Creation
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Email::Address
COMPONENT_ARCHIVE_HASH =	\
	sha256:0fa3785298cc2f6780e63e3a5fb1ca814dcbc360ceb59ed8fa84eb4ffa06f9ef
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/R/RJ/RJBS/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
