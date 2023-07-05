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
#   $WS_TOOLS/perl-integrate-module JSON::XS
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		JSON::XS
HUMAN_VERSION =			4.03
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		JSON::XS - JSON serialising/deserialising, done correctly and fast
COMPONENT_CPAN_AUTHOR =		MLEHMANN
COMPONENT_ARCHIVE_HASH =	\
	sha256:515536f45f2fa1a7e88c8824533758d0121d267ab9cb453a1b5887c8a56b9068
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Disable Canary::Stability prompt
COMPONENT_CONFIGURE_ENV += PERL_CANARY_STABILITY_NOPROMPT=1

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/canary-stability
PERL_REQUIRED_PACKAGES += library/perl-5/common-sense
PERL_REQUIRED_PACKAGES += library/perl-5/types-serialiser
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
