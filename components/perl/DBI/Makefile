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
#   $WS_TOOLS/perl-integrate-module DBI
#

BUILD_STYLE = makemaker
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		DBI
HUMAN_VERSION =			1.645
COMPONENT_SUMMARY =		DBI - Database independent interface for Perl
COMPONENT_ARCHIVE_URL =		\
	https://cpan.metacpan.org/authors/id/H/HM/HMBRAND/DBI-1.645.tgz
COMPONENT_ARCHIVE_HASH =	\
	sha256:e38b7a5efee129decda12383cf894963da971ffac303f54cc1b93e40e3cf9921
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# remove lines that changes with every test run
COMPONENT_TEST_TRANSFORMS += '-e "/^SV =/,/^[^ ]/d"'

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod-coverage

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
