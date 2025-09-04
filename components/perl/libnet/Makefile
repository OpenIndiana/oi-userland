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
#   $WS_TOOLS/perl-integrate-module libnet
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		libnet
HUMAN_VERSION =			3.16
COMPONENT_SUMMARY =		Collection of network protocol modules
COMPONENT_CPAN_AUTHOR =		SHAY
COMPONENT_ARCHIVE_HASH =	\
	sha256:41472b0047cba02c203d3d02b9d4cf72b41346997b26c79b459be6159b0c0875
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Prevent questions during configure
CONFIGURE_ENV += PERL5_CPAN_IS_RUNNING=1

# Auto-generated dependencies
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/socket
REQUIRED_PACKAGES.perl += library/perl-5/time-local
REQUIRED_PACKAGES.perl += runtime/perl
