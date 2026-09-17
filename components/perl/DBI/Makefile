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
HUMAN_VERSION =			1.653
COMPONENT_SUMMARY =		Database independent interface for Perl
COMPONENT_ARCHIVE_URL =		\
	https://cpan.metacpan.org/authors/id/H/HM/HMBRAND/DBI-1.653.tgz
COMPONENT_ARCHIVE_HASH =	\
	sha256:a98c21fd37eed8f841172875d175d972fe87f063d7d0d2a3b7765908bb25eb58
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod-coverage

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/encode
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/module-load
REQUIRED_PACKAGES.perl += library/perl-5/test-simple
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/clone
TEST_REQUIRED_PACKAGES.perl += library/perl-5/db_file
TEST_REQUIRED_PACKAGES.perl += library/perl-5/module-load
TEST_REQUIRED_PACKAGES.perl += library/perl-5/params-util
TEST_REQUIRED_PACKAGES.perl += library/perl-5/sql-statement
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
