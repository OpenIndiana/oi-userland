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
HUMAN_VERSION =			0.63
COMPONENT_SUMMARY =		DBI driver for CSV files
COMPONENT_ARCHIVE_URL =		\
	https://cpan.metacpan.org/authors/id/H/HM/HMBRAND/DBD-CSV-0.63.tgz
COMPONENT_ARCHIVE_HASH =	\
	sha256:0d9000e26c300fa23b056e3b65743ca16ceaae90997535d23b80fdea30ca568e
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
