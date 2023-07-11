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
#   $WS_TOOLS/perl-integrate-module Net::SSLeay
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Net::SSLeay
HUMAN_VERSION =			1.92
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Net::SSLeay - Perl bindings for OpenSSL and LibreSSL
COMPONENT_CPAN_AUTHOR =		CHRISN
COMPONENT_ARCHIVE_HASH =	\
	sha256:47c2f2b300f2e7162d71d699f633dd6a35b0625a00cbda8c50ac01144a9396a9
COMPONENT_LICENSE =		Artistic-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# The component Makefile.PL file will ask some questions on whether we want
# to run external tests, to which we want to answer with "n".
COMPONENT_CONFIGURE_ENV += ; echo "n" |

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
