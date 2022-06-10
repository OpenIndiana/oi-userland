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

COMPONENT_NAME =		Sub-Info
HUMAN_VERSION =			0.002
COMPONENT_VERSION =		0.2
COMPONENT_FMRI =		library/perl-5/sub-info
COMPONENT_SUMMARY =		Sub::Info - Tool for inspecting subroutines.
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Sub::Info
COMPONENT_ARCHIVE_HASH =	\
	sha256:ea3056d696bdeff21a99d340d5570887d39a8cc47bff23adfc82df6758cdd0ea
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/E/EX/EXODIST/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += library/perl-5/importer
REQUIRED_PACKAGES += library/perl-5/test-simple

# Auto-generated dependencies
