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

COMPONENT_NAME =		TimeDate
COMPONENT_VERSION =		2.33
COMPONENT_FMRI =		library/perl-5/timedate
COMPONENT_SUMMARY =		TimeDate - Parse date strings into time values
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/dist/TimeDate
COMPONENT_ARCHIVE_HASH =	\
	sha256:c0b69c4b039de6f501b0d9f13ec58c86b040c1f7e9b27ef249651c143d605eb2
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/A/AT/ATOOMIC/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
