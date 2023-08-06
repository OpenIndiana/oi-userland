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
#   $WS_TOOLS/perl-integrate-module Crypt::RIPEMD160
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Crypt::RIPEMD160
HUMAN_VERSION =			0.08
COMPONENT_SUMMARY =		Crypt::RIPEMD160 - Perl extension for the RIPEMD-160 Hash function
COMPONENT_CPAN_AUTHOR =		TODDR
COMPONENT_ARCHIVE_HASH =	\
	sha256:34d1c87607f6c9defab3741b76d31bccfbb6d4d201af80e0f6083c378130b232
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# Workaround for https://github.com/toddr/Crypt-RIPEMD160/issues/2
# see also https://www.perlmonks.org/?node_id=11107721
COMPONENT_POST_BUILD_ACTION += \
	$(MKDIR) $(@D)/blib/lib/auto/Crypt/RIPEMD160/MAC ; \
	echo "1;" > $(@D)/blib/lib/auto/Crypt/RIPEMD160/MAC/autosplit.ix ;

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
