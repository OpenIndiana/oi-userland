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

COMPONENT_NAME =		Test-Simple
HUMAN_VERSION =			1.302190
COMPONENT_VERSION =		1.302.190
COMPONENT_REVISION =		1
COMPONENT_FMRI =		library/perl-5/test-simple
COMPONENT_SUMMARY =		Test2 - Framework for writing test tools that all work together.
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/dist/Test-Simple
COMPONENT_ARCHIVE_HASH =	\
	sha256:fbb15226f1c605c4466a8c6ba02030083d54333d34fa76c02549cae7014c3a0e
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/E/EX/EXODIST/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

# We need Test2 part of this package only.  Perl distribution already bundles
# Test-Simple, but its version in 5.22 and 5.24 is so old that it does not
# contain Test2.  Perl 5.34 already bundles pretty recent Test-Simple so we do
# not need this package for 5.34 at all.
PERL_VERSIONS = 5.22 5.24
PERL_64_ONLY_VERSIONS = 5.24

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
