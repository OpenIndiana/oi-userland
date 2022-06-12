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

COMPONENT_NAME =		Alien-Build
COMPONENT_VERSION =		2.48
COMPONENT_FMRI =		library/perl-5/alien-build
COMPONENT_SUMMARY =		Alien::Build - Build external dependencies for use in CPAN
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Alien::Build
COMPONENT_ARCHIVE_HASH =	\
	sha256:3b26e4794f83c681f3eff8f9d052ba74262c1ca5bad30477a41e66ba64391696
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/P/PL/PLICEASE/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

# This package requires test2-suite which is not available for perl 5.22 and 5.24
# Remove this once both perl 5.22 and 5.24 are obsoleted
PERL_VERSIONS = 5.34
PERL_64_ONLY_VERSIONS = 5.34

include $(WS_MAKE_RULES)/common.mk

# Remove comments because they could change with every test run
COMPONENT_TEST_TRANSFORMS += '-e "/^\#/d"'

PERL_REQUIRED_PACKAGES += library/perl-5/capture-tiny
PERL_REQUIRED_PACKAGES += library/perl-5/ffi-checklib
PERL_REQUIRED_PACKAGES += library/perl-5/file-chdir
PERL_REQUIRED_PACKAGES += library/perl-5/file-which
PERL_REQUIRED_PACKAGES += library/perl-5/path-tiny
PERL_REQUIRED_PACKAGES += library/perl-5/pkgconfig
PERL_REQUIRED_PACKAGES += library/perl-5/test2-suite

# Auto-generated dependencies
