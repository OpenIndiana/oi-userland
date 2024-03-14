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
#   $WS_TOOLS/perl-integrate-module DBD::CSV
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		DBD::CSV
HUMAN_VERSION =			0.60
COMPONENT_SUMMARY =		DBD::CSV - DBI driver for CSV files
COMPONENT_ARCHIVE_URL=		https://cpan.metacpan.org/authors/id/H/HM/HMBRAND/DBD-CSV-0.60.tgz
COMPONENT_ARCHIVE_HASH =	\
	sha256:018b83a30f799979bc8c3c3044c8b1c8001cdf60bdc3e746848818195254b4e7
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Avoid questions during configure phase
COMMON_PERL_ENV += AUTOMATED_TESTING=1

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/dbi
PERL_REQUIRED_PACKAGES += library/perl-5/sql-statement
PERL_REQUIRED_PACKAGES += library/perl-5/text-csv_xs
PERL_REQUIRED_PACKAGES += runtime/perl
