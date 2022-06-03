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

COMPONENT_NAME =		CPAN-Meta-Check
HUMAN_VERSION =			0.014
COMPONENT_VERSION =		0.14
COMPONENT_FMRI =		library/perl-5/cpan-meta-check
COMPONENT_SUMMARY =		CPAN::Meta::Check - Verify requirements in a CPAN::Meta object
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/CPAN::Meta::Check
COMPONENT_ARCHIVE_HASH =	\
	sha256:28a0572bfc1c0678d9ce7da48cf521097ada230f96eb3d063fcbae1cfe6a351f
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/L/LE/LEONT/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
