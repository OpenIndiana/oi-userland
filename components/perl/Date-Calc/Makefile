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
#   $WS_TOOLS/perl-integrate-module Date::Calc
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Date::Calc
HUMAN_VERSION =			6.4
COMPONENT_REVISION =		3
COMPONENT_SUMMARY =		Date::Calc - Gregorian calendar date calculations
COMPONENT_CPAN_AUTHOR =		STBEY
COMPONENT_ARCHIVE_HASH =	\
	sha256:7ce137b2e797b7c0901f3adf1a05a19343356cd1f04676aa1c56a9f624f859ad
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-2.0-only OR LGPL-2.0-only

include $(WS_MAKE_RULES)/common.mk

#
# There is circular runtime dependency:
#
#	Date-Calc recommends Date-Calc-XS
#	Date-Calc-XS requires Date-Calc
#
# To bootstrap both components we need to build Date-Calc first and remove any
# unresolved runtime dependency on Date-Calc-XS.
#
MANGLE_DEPEND_RUNTIME += | \
	$(GNU_GREP) -v '^depend type=require fmri=__TBD pkg\.debug\.depend\.file=Date/Calc/XS\.pm'

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/bit-vector
PERL_REQUIRED_PACKAGES += library/perl-5/carp-clan
PERL_REQUIRED_PACKAGES += library/perl-5/date-calc-xs
PERL_REQUIRED_PACKAGES += runtime/perl
