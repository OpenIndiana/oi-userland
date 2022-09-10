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

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Clone
HUMAN_VERSION =			0.45
COMPONENT_SUMMARY =		Clone - recursively copy Perl datatypes
COMPONENT_CPAN_AUTHOR =		ATOOMIC
COMPONENT_ARCHIVE_HASH =	\
	sha256:cbb6ee348afa95432e4878893b46752549e70dc68fe6d9e430d1d2e99079a9e6
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_TRANSFORMS += "-e '/^SV/d'"
COMPONENT_TEST_TRANSFORMS += "-e '/PV/d'"
COMPONENT_TEST_TRANSFORMS += "-e '/MG_PTR/d'"
COMPONENT_TEST_TRANSFORMS += "-e '/MAGIC/d'"

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/b-cow
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
