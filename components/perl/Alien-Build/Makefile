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
#   $WS_TOOLS/perl-integrate-module Alien::Build
#

BUILD_STYLE = makemaker
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Alien::Build
HUMAN_VERSION =			2.83
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Alien::Build - Build external dependencies for use in CPAN
COMPONENT_CPAN_AUTHOR =		PLICEASE
COMPONENT_ARCHIVE_HASH =	\
	sha256:4817270314431350ff397125547f55641dcff98bdde213b9e5efc613f7c8b85a
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/readonly

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/capture-tiny
PERL_REQUIRED_PACKAGES += library/perl-5/ffi-checklib
PERL_REQUIRED_PACKAGES += library/perl-5/file-chdir
PERL_REQUIRED_PACKAGES += library/perl-5/file-which
PERL_REQUIRED_PACKAGES += library/perl-5/path-tiny
PERL_REQUIRED_PACKAGES += library/perl-5/pkgconfig
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/devel-hide
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test2-suite
