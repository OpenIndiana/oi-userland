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
# Copyright 2022 Marcel Telka
#

BUILD_STYLE = makemaker
BUILD_BITS = 32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Email-Stuffer
HUMAN_VERSION =			0.018
COMPONENT_VERSION =		0.18
COMPONENT_FMRI =		library/perl-5/email-stuffer
COMPONENT_SUMMARY =		Email::Stuffer - A more casual approach to creating and sending Email:: emails
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Email::Stuffer
COMPONENT_ARCHIVE_HASH =	\
	sha256:d000a28ef0963699b1eb2b4e469b58ab7c3a0cfa4a74319e0e746156e1bd8a0b
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/R/RJ/RJBS/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

PERL_REQUIRED_PACKAGES += library/perl-5/email-mime
PERL_REQUIRED_PACKAGES += library/perl-5/email-sender
PERL_REQUIRED_PACKAGES += library/perl-5/module-runtime
PERL_REQUIRED_PACKAGES += library/perl-5/moo
PERL_REQUIRED_PACKAGES += library/perl-5/params-util
PERL_REQUIRED_PACKAGES += library/perl-5/test-fatal

# Auto-generated dependencies
