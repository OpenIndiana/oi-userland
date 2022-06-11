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

COMPONENT_NAME =		Email-Sender
HUMAN_VERSION =			1.300021
COMPONENT_VERSION =		1.3.21
COMPONENT_FMRI =		library/perl-5/email-sender
COMPONENT_SUMMARY =		Email::Sender - a library for sending email
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Email::Sender
COMPONENT_ARCHIVE_HASH =	\
	sha256:f565ef5805ff54c5a77400b0a512709137092d247321bbe5065f265e2a7b4fed
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/R/RJ/RJBS/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

PERL_REQUIRED_PACKAGES += library/perl-5/capture-tiny
PERL_REQUIRED_PACKAGES += library/perl-5/email-abstract
PERL_REQUIRED_PACKAGES += library/perl-5/email-address
PERL_REQUIRED_PACKAGES += library/perl-5/email-simple
PERL_REQUIRED_PACKAGES += library/perl-5/list-moreutils
PERL_REQUIRED_PACKAGES += library/perl-5/module-runtime
PERL_REQUIRED_PACKAGES += library/perl-5/moo
PERL_REQUIRED_PACKAGES += library/perl-5/moox-types-mooselike
PERL_REQUIRED_PACKAGES += library/perl-5/sub-exporter
PERL_REQUIRED_PACKAGES += library/perl-5/throwable
PERL_REQUIRED_PACKAGES += library/perl-5/try-tiny

# Auto-generated dependencies
