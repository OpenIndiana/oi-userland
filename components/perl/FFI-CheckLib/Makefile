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
HUMAN_VERSION =			0.28
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		FFI::CheckLib - Check that a library is available for FFI
COMPONENT_CPAN_AUTHOR =		PLICEASE
COMPONENT_ARCHIVE_HASH =	\
	sha256:cf377ce735b332c41f600ca6c5e87af30db6c3787f9b67d50a245d1ebe6fc350
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/test2-suite
PERL_REQUIRED_PACKAGES += runtime/perl
