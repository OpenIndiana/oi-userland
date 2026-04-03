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
#   $WS_TOOLS/perl-integrate-module IO-Tty
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		IO-Tty
HUMAN_VERSION =			1.26
COMPONENT_SUMMARY =		Pseudo ttys and constants
COMPONENT_CPAN_AUTHOR =		TODDR
COMPONENT_ARCHIVE_HASH =	\
	sha256:89f1ff869f929af8ffb6b65255c6c5b639acc42df032a309a40c676ef6afbc76
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# This line varies between test runs
COMPONENT_TEST_TRANSFORMS += '-e "/^trying to open \/dev\/pts\//d"'

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
