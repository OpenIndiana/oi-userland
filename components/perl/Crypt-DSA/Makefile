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
#   $WS_TOOLS/perl-integrate-module Crypt::DSA
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Crypt::DSA
HUMAN_VERSION =			1.17
COMPONENT_SUMMARY =		Crypt::DSA - DSA Signatures and Key Generation
COMPONENT_CPAN_AUTHOR =		ADAMK
COMPONENT_ARCHIVE_HASH =	\
	sha256:d1b8585f6bf746f76e5dc5da3641d325ed656bc2e5f344b54514b55c31009a03
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-2.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Makefile.PL needs to find bundled inc::Module::Install
COMPONENT_CONFIGURE_ENV += PERL5LIB=$(@D)

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/data-buffer
PERL_REQUIRED_PACKAGES += library/perl-5/digest-sha1
PERL_REQUIRED_PACKAGES += library/perl-5/file-which
PERL_REQUIRED_PACKAGES += runtime/perl
