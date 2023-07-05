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
#   $WS_TOOLS/perl-integrate-module Clone
#

BUILD_STYLE = makemaker
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Clone
HUMAN_VERSION =			0.46
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Clone - recursively copy Perl datatypes
COMPONENT_CPAN_AUTHOR =		GARU
COMPONENT_ARCHIVE_HASH =	\
	sha256:aadeed5e4c8bd6bbdf68c0dd0066cb513e16ab9e5b4382dc4a0aafd55890697b
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Pointers varies with every run
COMPONENT_TEST_TRANSFORMS += "-e 's/0x[0-9a-f]\{1,\}/POINTER/g'"

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.perl += library/perl-5/b-cow
