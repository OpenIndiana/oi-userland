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

COMPONENT_NAME =		Term-Table
HUMAN_VERSION =			0.016
COMPONENT_VERSION =		0.16
COMPONENT_FMRI =		library/perl-5/term-table
COMPONENT_SUMMARY =		Term::Table - Format a header and rows into a table
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Term::Table
COMPONENT_ARCHIVE_HASH =	\
	sha256:8fb4fbb8e96a2d6c514949eb8cfd7e66319bcb1cbf7cea0ab19af887a72d97bf
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/E/EX/EXODIST/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += library/perl-5/importer
REQUIRED_PACKAGES += library/perl-5/test-simple

# Auto-generated dependencies
