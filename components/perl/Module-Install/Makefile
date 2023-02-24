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
#   $WS_TOOLS/perl-integrate-module Module::Install
#

BUILD_STYLE = makemaker
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Module::Install
HUMAN_VERSION =			1.19
COMPONENT_SUMMARY =		Module::Install - Standalone, extensible Perl module installer
COMPONENT_CPAN_AUTHOR =		ETHER
COMPONENT_ARCHIVE_HASH =	\
	sha256:1a53a78ddf3ab9e3c03fc5e354b436319a944cba4281baf0b904fa932a13011b
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# remove lines that contain perl warnings
COMPONENT_TEST_TRANSFORMS += "-e '/^Use of uninitialized value/d' -e '/^old INSTALLDIRS/d'"

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/file-remove
PERL_REQUIRED_PACKAGES += library/perl-5/module-build
PERL_REQUIRED_PACKAGES += library/perl-5/module-scandeps
PERL_REQUIRED_PACKAGES += library/perl-5/yaml-tiny
PERL_REQUIRED_PACKAGES += runtime/perl
