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

COMPONENT_NAME =		List-MoreUtils-XS
COMPONENT_VERSION =		0.430
COMPONENT_FMRI =		library/perl-5/list-moreutils-xs
COMPONENT_SUMMARY =		List::MoreUtils::XS - Provide compiled List::MoreUtils functions
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/List::MoreUtils::XS
COMPONENT_ARCHIVE_HASH =	\
	sha256:e8ce46d57c179eecd8758293e9400ff300aaf20fefe0a9d15b9fe2302b9cb242
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/R/RE/REHSACK/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Apache v2.0

include $(WS_MAKE_RULES)/common.mk

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
