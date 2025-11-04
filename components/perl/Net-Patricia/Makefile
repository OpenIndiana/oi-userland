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
#   $WS_TOOLS/perl-integrate-module Net-Patricia
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Net-Patricia
HUMAN_VERSION =			1.24
COMPONENT_SUMMARY =		Patricia Trie for fast IP address lookups
COMPONENT_CPAN_AUTHOR =		GRUBER
COMPONENT_ARCHIVE_HASH =	\
	sha256:d94f520804e2541b1cd20e73366720a973caf5dd2d2623838fc8d6398afd7edb
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	COPYING

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/net-cidr-lite
REQUIRED_PACKAGES.perl += library/perl-5/socket
REQUIRED_PACKAGES.perl += library/perl-5/socket6
REQUIRED_PACKAGES.perl += library/perl-5/version
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
