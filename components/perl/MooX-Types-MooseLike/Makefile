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

COMPONENT_NAME =		MooX-Types-MooseLike
COMPONENT_VERSION =		0.29
COMPONENT_FMRI =		library/perl-5/moox-types-mooselike
COMPONENT_SUMMARY =		MooX::Types::MooseLike - some Moosish types and a type builder
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/MooX::Types::MooseLike
COMPONENT_ARCHIVE_HASH =	\
	sha256:1d3780aa9bea430afbe65aa8c76e718f1045ce788aadda4116f59d3b7a7ad2b4
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/M/MA/MATEU/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += library/perl-5/module-runtime
REQUIRED_PACKAGES += library/perl-5/moo
REQUIRED_PACKAGES += library/perl-5/test-fatal

# Auto-generated dependencies
