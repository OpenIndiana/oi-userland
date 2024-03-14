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
#   $WS_TOOLS/perl-integrate-module Authen::PAM
#

BUILD_STYLE = makemaker
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Authen::PAM
HUMAN_VERSION =			0.16
COMPONENT_REVISION =		7
COMPONENT_SUMMARY =		Authen::PAM - Perl interface to PAM library
COMPONENT_CPAN_AUTHOR =		NIKIP
COMPONENT_ARCHIVE_HASH =	\
	sha256:0e949bd9a2a9df0f829971030fe9169cbaf6cec78b92faf22f547ff6c6155c9b
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# 01-solaris.patch modified configure.ac so we need to run autoconf
COMPONENT_PREP_ACTION = ( cd $(@D) && autoconf )

# Drop machine specific info
COMPONENT_TEST_TRANSFORMS += "-e '/^----/d'"

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
