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
#   $WS_TOOLS/perl-integrate-module Test-Harness
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Test-Harness
HUMAN_VERSION =			3.52
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		contributing to TAP::Harness
COMPONENT_CPAN_AUTHOR =		LEONT
COMPONENT_ARCHIVE_HASH =	\
	sha256:8fe65cfc0261ed3c8a4395f0524286f5719669fe305f9b03b16cf3684d62cd70
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# The t/source.t test expects there are no symlinks
CLONEY_MODE = hardlink

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/pod-usage
PERL_REQUIRED_PACKAGES += runtime/perl
