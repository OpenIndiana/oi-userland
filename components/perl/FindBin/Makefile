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

COMPONENT_NAME =		FindBin
COMPONENT_VERSION =		1.52
COMPONENT_FMRI =		library/perl-5/findbin
COMPONENT_SUMMARY =		FindBin - Locate directory of original perl script
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/FindBin
COMPONENT_ARCHIVE_HASH =	\
	sha256:ea3cbc1eaa36cccbe1a79a818fba07a8ce9dbf729d120d0823d36c55e8256c19
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/T/TO/TODDR/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
