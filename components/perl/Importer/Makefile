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

COMPONENT_NAME =		Importer
HUMAN_VERSION =			0.026
COMPONENT_VERSION =		0.26
COMPONENT_FMRI =		library/perl-5/importer
COMPONENT_SUMMARY =		Importer - Alternative but compatible interface to modules that export symbols.
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Importer
COMPONENT_ARCHIVE_HASH =	\
	sha256:e08fa84e13cb998b7a897fc8ec9c3459fcc1716aff25cc343e36ef875891b0ef
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/E/EX/EXODIST/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
