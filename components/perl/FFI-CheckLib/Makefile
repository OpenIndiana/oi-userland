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
#   $WS_TOOLS/perl-integrate-module FFI::CheckLib
#

BUILD_STYLE = makemaker
# With default "symlink" cloney mode tests fails
# see https://github.com/PerlFFI/FFI-CheckLib/issues/43
CLONEY_ARGS = CLONEY_MODE="hardlink"

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		FFI::CheckLib
HUMAN_VERSION =			0.31
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		FFI::CheckLib - Check that a library is available for FFI
COMPONENT_CPAN_AUTHOR =		PLICEASE
COMPONENT_ARCHIVE_HASH =	\
	sha256:04d885fc377d44896e5ea1c4ec310f979bb04f2f18658a7e7a4d509f7e80bb80
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/file-which
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test2-suite
