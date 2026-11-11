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
#   $WS_TOOLS/perl-integrate-module Encode
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Encode
HUMAN_VERSION =			3.25
COMPONENT_SUMMARY =		character encodings in Perl
COMPONENT_CPAN_AUTHOR =		DANKOGAI
COMPONENT_ARCHIVE_HASH =	\
	sha256:28a83ef0e6a9740326e9a3e4cc523b1f1129d7692e580a2005a6117c646dfca7
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# The t/piconv.t test fails when there are symlinks
CLONEY_MODE = hardlink

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/parent
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
