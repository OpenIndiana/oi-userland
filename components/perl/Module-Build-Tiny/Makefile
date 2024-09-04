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
# This file was automatically generated using the following command:
#   $WS_TOOLS/perl-integrate-module Module::Build::Tiny
#

BUILD_STYLE = modulebuild

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Module::Build::Tiny
HUMAN_VERSION =			0.049
COMPONENT_SUMMARY =		Module::Build::Tiny - A tiny replacement for Module::Build
COMPONENT_CPAN_AUTHOR =		LEONT
COMPONENT_ARCHIVE_HASH =	\
	sha256:61b0207708dc1899dad2111f92afa6f88c26e8e9c946e28a0dbbb9e9b8082f18
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

# Module::Build::Tiny >= 0.048 needs CPAN::Requirements::Dynamic which in
# turn requires CPAN::Meta::Requirements >= 2.143.
# The CPAN::Meta::Requirements module is in Perl core, but Perl <= 5.38
# contains version 2.140 only.
PERL_VERSIONS := $(filter-out 5.36 5.38, $(PERL_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/cpan-requirements-dynamic
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-config
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-helpers
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-installpaths
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/file-sharedir
