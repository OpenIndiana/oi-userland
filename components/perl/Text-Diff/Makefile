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

COMPONENT_NAME =		Text-Diff
COMPONENT_VERSION =		1.45
COMPONENT_FMRI =		library/perl-5/text-diff
COMPONENT_SUMMARY =		Text::Diff - Perform diffs on files and record sets
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Text::Diff
COMPONENT_ARCHIVE_HASH =	\
	sha256:e8baa07b1b3f53e00af3636898bbf73aec9a0ff38f94536ede1dbe96ef086f04
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/N/NE/NEILB/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += library/perl-5/algorithm-diff

# Auto-generated dependencies
