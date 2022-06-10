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

COMPONENT_NAME =		Eval-Closure
COMPONENT_VERSION =		0.14
COMPONENT_FMRI =		library/perl-5/eval-closure
COMPONENT_SUMMARY =		Eval::Closure - safely and cleanly create closures via string eval
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Eval::Closure
COMPONENT_ARCHIVE_HASH =	\
	sha256:ea0944f2f5ec98d895bef6d503e6e4a376fea6383a6bc64c7670d46ff2218cad
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/D/DO/DOY/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += library/perl-5/test-fatal
REQUIRED_PACKAGES += library/perl-5/test-requires

# Auto-generated dependencies
