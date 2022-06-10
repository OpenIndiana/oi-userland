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

COMPONENT_NAME =		Test-Differences
COMPONENT_VERSION =		0.69
COMPONENT_FMRI =		library/perl-5/test-differences
COMPONENT_SUMMARY =		Test::Differences - Test strings and data structures and show differences if not ok
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Test::Differences
COMPONENT_ARCHIVE_HASH =	\
	sha256:18f644fdd4a1fef93ef3f7f67df8e95b593d811899f34bcbbaba4d717222f58f
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/D/DC/DCANTRELL/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += library/perl-5/capture-tiny
REQUIRED_PACKAGES += library/perl-5/text-diff

# Auto-generated dependencies
