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
#   $WS_TOOLS/perl-integrate-module JSON-XS
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		JSON-XS
HUMAN_VERSION =			4.04
COMPONENT_SUMMARY =		JSON serialising/deserialising, done correctly and fast
COMPONENT_CPAN_AUTHOR =		MLEHMANN
COMPONENT_ARCHIVE_HASH =	\
	sha256:8eff1e9f304c5625b59ab7b42258415f6d3e3681c1ddab6b725518a018a7f5e0
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Disable Canary::Stability prompt
CONFIGURE_ENV += PERL_CANARY_STABILITY_NOPROMPT=1

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/canary-stability
REQUIRED_PACKAGES.perl += library/perl-5/common-sense
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/types-serialiser
REQUIRED_PACKAGES.perl += runtime/perl
