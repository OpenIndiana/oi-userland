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
#   $WS_TOOLS/perl-integrate-module PkgConfig
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		PkgConfig
HUMAN_VERSION =			0.26026
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Pure-Perl Core-Only replacement for pkg-config
COMPONENT_CPAN_AUTHOR =		PLICEASE
COMPONENT_ARCHIVE_HASH =	\
	sha256:5352ed156a4b5de8c523771ee399f6f8ce5e8bfcf8674f1e1dbd4a8c83643b85
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# remove line with perl version
COMPONENT_TEST_TRANSFORMS += '-e "/^Testing PkgConfig .*, Perl .*/d"'

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/capture-tiny

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/test-simple
PERL_REQUIRED_PACKAGES += runtime/perl
