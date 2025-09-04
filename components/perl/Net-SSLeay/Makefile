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
#   $WS_TOOLS/perl-integrate-module Net-SSLeay
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Net-SSLeay
HUMAN_VERSION =			1.96
COMPONENT_SUMMARY =		Perl bindings for OpenSSL and LibreSSL
COMPONENT_CPAN_AUTHOR =		CHRISN
COMPONENT_ARCHIVE_HASH =	\
	sha256:ab213691685fb2a576c669cbc8d9266f8165a31563ad15b7c4030b94adfc0753
COMPONENT_LICENSE =		Artistic-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# The component Makefile.PL file will ask some questions on whether we want
# to run external tests, to which we want to answer with "n".
CONFIGURE_ENV += echo "n" |


include $(WS_MAKE_RULES)/common.mk

# Set OPENSSL_PREFIX so Makefile.PL is able to find our preferred OpenSSL
CONFIGURE_ENV += OPENSSL_PREFIX=$(OPENSSL_PREFIX)

# Optional test dependencies missing from metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/mime-base64
REQUIRED_PACKAGES.perl += library/perl-5/text-tabs+wrap
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/scalar-list-utils
TEST_REQUIRED_PACKAGES.perl += library/perl-5/socket
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
