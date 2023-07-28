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
#   $WS_TOOLS/perl-integrate-module Email::Stuffer
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Email::Stuffer
HUMAN_VERSION =			0.020
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Email::Stuffer - A more casual approach to creating and sending Email:: emails
COMPONENT_CPAN_AUTHOR =		RJBS
COMPONENT_ARCHIVE_HASH =	\
	sha256:0a1efb7f2dedd39052b126f718ca2d3b5845a4123a39392fd9dfa0c76e6057c7
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/email-mime
PERL_REQUIRED_PACKAGES += library/perl-5/email-sender
PERL_REQUIRED_PACKAGES += library/perl-5/module-runtime
PERL_REQUIRED_PACKAGES += library/perl-5/params-util
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/email-sender
TEST_REQUIRED_PACKAGES.perl += library/perl-5/moo
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-fatal
