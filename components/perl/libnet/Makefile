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
HUMAN_VERSION =			3.15
COMPONENT_REVISION =		4
COMPONENT_SUMMARY =		Collection of network protocol modules
COMPONENT_CPAN_AUTHOR =		SHAY
COMPONENT_ARCHIVE_HASH =	\
	sha256:a71f4db580e1a767d6936faa5baf38f1fa617824342da078b561283e86f8f4a2
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Prevent questions during configure
COMPONENT_CONFIGURE_ENV += PERL5_CPAN_IS_RUNNING=1

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-makemaker
PERL_REQUIRED_PACKAGES += library/perl-5/socket
PERL_REQUIRED_PACKAGES += library/perl-5/time-local
PERL_REQUIRED_PACKAGES += runtime/perl
