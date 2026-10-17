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
#   $WS_TOOLS/perl-integrate-module Alien-Build
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Alien-Build
HUMAN_VERSION =			2.88
COMPONENT_SUMMARY =		Build external dependencies for use in CPAN
COMPONENT_CPAN_AUTHOR =		PLICEASE
COMPONENT_ARCHIVE_HASH =	\
	sha256:c14346bace2b50cae62f1ee70a907f4c7383fabf90b034272ee52a5b1345fbba
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# Alien-Build --> Alien-cmake3 ==> Alien-Build
#
# To break loops we need to allow this component to integrate without testing in
# a case the required packages are not available yet (bootstrap).
#
PERL_TEST_BOOTSTRAP = yes

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/alien-cmake3
TEST_REQUIRED_PACKAGES.perl += library/perl-5/readonly

# Auto-generated dependencies
REQUIRED_PACKAGES.perl += library/perl-5/capture-tiny
REQUIRED_PACKAGES.perl += library/perl-5/digest-sha
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/ffi-checklib
REQUIRED_PACKAGES.perl += library/perl-5/file-chdir
REQUIRED_PACKAGES.perl += library/perl-5/file-which
REQUIRED_PACKAGES.perl += library/perl-5/json-pp
REQUIRED_PACKAGES.perl += library/perl-5/parent
REQUIRED_PACKAGES.perl += library/perl-5/path-tiny
REQUIRED_PACKAGES.perl += library/perl-5/pkgconfig
REQUIRED_PACKAGES.perl += library/perl-5/scalar-list-utils
REQUIRED_PACKAGES.perl += library/perl-5/test-simple
REQUIRED_PACKAGES.perl += library/perl-5/text-parsewords
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/archive-tar
TEST_REQUIRED_PACKAGES.perl += library/perl-5/devel-hide
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
