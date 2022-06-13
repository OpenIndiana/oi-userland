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

COMPONENT_NAME =		common-sense
COMPONENT_VERSION =		3.75
COMPONENT_FMRI =		library/perl-5/common-sense
COMPONENT_SUMMARY =		common::sense - save a tree AND a kitten, use common::sense!
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/common::sense
COMPONENT_ARCHIVE_HASH =	\
	sha256:a86a1c4ca4f3006d7479064425a09fa5b6689e57261fcb994fe67d061cba0e7e
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/M/ML/MLEHMANN/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
