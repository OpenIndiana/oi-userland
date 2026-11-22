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
#   $WS_TOOLS/perl-integrate-module Bit-Vector
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Bit-Vector
HUMAN_VERSION =			7.5
COMPONENT_SUMMARY =		Efficient bit vector, set of integers and \\\\\\\"big int\\\\\\\" math library
COMPONENT_CPAN_AUTHOR =		SHLOMIF
COMPONENT_ARCHIVE_HASH =	\
	sha256:23979226b47db204b80eb3358fa49bd27322a239dc109b51bcdebb91548e818e
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-2.0-only OR LGPL-2.0-only

include $(WS_MAKE_RULES)/common.mk

# The argument can vary
COMPONENT_TEST_TRANSFORMS += "-e 's/\(Argument \"\)[^ ]\+\(\" isn'\''t numeric\)/\1XXXXXXXX\2/g'"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/carp-clan
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += runtime/perl
