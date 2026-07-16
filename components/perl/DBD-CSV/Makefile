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
#   $WS_TOOLS/perl-integrate-module DBD-CSV
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		DBD-CSV
HUMAN_VERSION =			0.64
COMPONENT_SUMMARY =		DBI driver for CSV files
COMPONENT_ARCHIVE_URL =		\
	https://cpan.metacpan.org/authors/id/H/HM/HMBRAND/DBD-CSV-0.64.tgz
COMPONENT_ARCHIVE_HASH =	\
	sha256:7d4d8e54957c75fb374ab27d4e8729affe62e2e13da0c347e9a9088f39c735ae
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Avoid questions during configure phase
COMMON_PERL_ENV += AUTOMATED_TESTING=1

# Auto-generated dependencies
REQUIRED_PACKAGES.perl += library/perl-5/dbi
REQUIRED_PACKAGES.perl += library/perl-5/encode
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/sql-statement
REQUIRED_PACKAGES.perl += library/perl-5/test-simple
REQUIRED_PACKAGES.perl += library/perl-5/text-csv_xs
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/encode
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-harness
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
