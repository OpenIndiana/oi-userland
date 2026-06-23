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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		DBI
HUMAN_VERSION =			1.649
COMPONENT_SUMMARY =		Database independent interface for Perl
COMPONENT_ARCHIVE_URL =		\
	https://cpan.metacpan.org/authors/id/H/HM/HMBRAND/DBI-1.649.tgz
COMPONENT_ARCHIVE_HASH =	\
	sha256:98897cdd06adae70e5516042e47ca08d623db2139fc58fd95cde208adf85c697
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# The hash varies with every run
COMPONENT_TEST_TRANSFORMS += "-e 's/\(HASH(0x\)[0-9a-f]\{6\})/\1XXXXXX)/g'"

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod-coverage

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/test-simple
REQUIRED_PACKAGES.perl += runtime/perl
