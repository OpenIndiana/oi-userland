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
HUMAN_VERSION =			2.84
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Build external dependencies for use in CPAN
COMPONENT_CPAN_AUTHOR =		PLICEASE
COMPONENT_ARCHIVE_HASH =	\
	sha256:8e891fd3acbac39dd8fdc01376b9abff931e625be41e0910ca30ad59363b4477
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
PERL_REQUIRED_PACKAGES += library/perl-5/capture-tiny
PERL_REQUIRED_PACKAGES += library/perl-5/digest-sha
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/ffi-checklib
PERL_REQUIRED_PACKAGES += library/perl-5/file-chdir
PERL_REQUIRED_PACKAGES += library/perl-5/file-which
PERL_REQUIRED_PACKAGES += library/perl-5/json-pp
PERL_REQUIRED_PACKAGES += library/perl-5/parent
PERL_REQUIRED_PACKAGES += library/perl-5/path-tiny
PERL_REQUIRED_PACKAGES += library/perl-5/pkgconfig
PERL_REQUIRED_PACKAGES += library/perl-5/scalar-list-utils
PERL_REQUIRED_PACKAGES += library/perl-5/test-simple
PERL_REQUIRED_PACKAGES += library/perl-5/text-parsewords
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/archive-tar
TEST_REQUIRED_PACKAGES.perl += library/perl-5/devel-hide
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
