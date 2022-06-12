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

COMPONENT_NAME =		Test2-Suite
HUMAN_VERSION =			0.000145
COMPONENT_VERSION =		0.0.145
COMPONENT_FMRI =		library/perl-5/test2-suite
COMPONENT_SUMMARY =		Test2::Suite - Distribution with a rich set of tools built upon the Test2 framework.
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Test2::Suite
COMPONENT_ARCHIVE_HASH =	\
	sha256:ed44be739c8879fe178d3107b238f2db960d52797db0058de53be5b84600358b
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/E/EX/EXODIST/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

# This package does not work well with perl 5.22 and 5.24
# Remove this once both perl 5.22 and 5.24 are obsoleted
PERL_VERSIONS = 5.34
PERL_64_ONLY_VERSIONS = 5.34

include $(WS_MAKE_RULES)/common.mk

PERL_REQUIRED_PACKAGES += library/perl-5/importer
PERL_REQUIRED_PACKAGES += library/perl-5/module-pluggable
PERL_REQUIRED_PACKAGES += library/perl-5/scope-guard
PERL_REQUIRED_PACKAGES += library/perl-5/sub-info
PERL_REQUIRED_PACKAGES += library/perl-5/term-table

# Auto-generated dependencies
