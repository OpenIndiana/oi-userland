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
#   $WS_TOOLS/perl-integrate-module HTML::Tree
#

BUILD_STYLE = modulebuild

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		HTML::Tree
HUMAN_VERSION =			5.07
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		HTML::Tree - build and scan parse-trees of HTML
COMPONENT_CPAN_AUTHOR =		KENTNL
COMPONENT_ARCHIVE_HASH =	\
	sha256:f0374db84731c204b86c1d5b90975fef0d30a86bd9def919343e554e31a9dbbf
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

#
# There is circular runtime dependency:
#
#	HTML-Tree recommends HTML-Formatter
#	HTML-Formatter requires HTML-Tree
#
# To bootstrap both components we need to build HTML-Tree first and remove any
# unresolved runtime dependency on HTML-Formatter.
#
MANGLE_DEPEND_RUNTIME += | \
	$(GNU_GREP) -v '^depend type=require fmri=__TBD pkg\.debug\.depend\.file=HTML/FormatText\.pm'

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/html-parser
PERL_REQUIRED_PACKAGES += library/perl-5/html-tagset
PERL_REQUIRED_PACKAGES += library/perl-5/libwww-perl
PERL_REQUIRED_PACKAGES += library/perl-5/module-build
PERL_REQUIRED_PACKAGES += library/perl-5/test-fatal
PERL_REQUIRED_PACKAGES += runtime/perl
