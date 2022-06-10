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

COMPONENT_NAME =		Test-Memory-Cycle
HUMAN_VERSION =			1.06
COMPONENT_VERSION =		1.6
COMPONENT_FMRI =		library/perl-5/test-memory-cycle
COMPONENT_SUMMARY =		Test::Memory::Cycle - Check for memory leaks and circular memory references
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Test::Memory::Cycle
COMPONENT_ARCHIVE_HASH =	\
	sha256:9d53ddfdc964cd8454cb0da4c695b6a3ae47b45839291c34cb9d8d1cfaab3202
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/P/PE/PETDANCE/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += library/perl-5/devel-cycle
REQUIRED_PACKAGES += library/perl-5/padwalker

# Auto-generated dependencies
