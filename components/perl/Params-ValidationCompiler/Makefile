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

COMPONENT_NAME =		Params-ValidationCompiler
COMPONENT_VERSION =		0.30
COMPONENT_FMRI =		library/perl-5/params-validationcompiler
COMPONENT_SUMMARY =		Params::ValidationCompiler - Build an optimized subroutine parameter validator once, use it forever
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Params::ValidationCompiler
COMPONENT_ARCHIVE_HASH =	\
	sha256:dc5bee23383be42765073db284bed9fbd819d4705ad649c20b644452090d16cb
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/D/DR/DROLSKY/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

# This package requires test2-plugin-nowarnings and test2-suite which are not available for perl 5.22 and 5.24
# Remove this once both perl 5.22 and 5.24 are obsoleted
PERL_VERSIONS = 5.34
PERL_64_ONLY_VERSIONS = 5.34

include $(WS_MAKE_RULES)/common.mk

PERL_REQUIRED_PACKAGES += library/perl-5/eval-closure
PERL_REQUIRED_PACKAGES += library/perl-5/exception-class
PERL_REQUIRED_PACKAGES += library/perl-5/specio
PERL_REQUIRED_PACKAGES += library/perl-5/test-without-module
PERL_REQUIRED_PACKAGES += library/perl-5/test2-plugin-nowarnings
PERL_REQUIRED_PACKAGES += library/perl-5/test2-suite

# Auto-generated dependencies
