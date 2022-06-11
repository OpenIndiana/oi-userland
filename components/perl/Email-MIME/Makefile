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

COMPONENT_NAME =		Email-MIME
COMPONENT_VERSION =		1.945
COMPONENT_FMRI =		library/perl-5/email-mime
COMPONENT_SUMMARY =		Email::MIME - easy MIME message handling
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Email::MIME
COMPONENT_ARCHIVE_HASH =	\
	sha256:64401b9b2cb5e1f769158ba6223ad3d4e5c5c17573d79e1c9410aaa907fc05ff
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/R/RJ/RJBS/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

PERL_REQUIRED_PACKAGES += library/perl-5/email-address-xs
PERL_REQUIRED_PACKAGES += library/perl-5/email-messageid
PERL_REQUIRED_PACKAGES += library/perl-5/email-mime-contenttype
PERL_REQUIRED_PACKAGES += library/perl-5/email-mime-encodings
PERL_REQUIRED_PACKAGES += library/perl-5/email-simple
PERL_REQUIRED_PACKAGES += library/perl-5/mime-types
PERL_REQUIRED_PACKAGES += library/perl-5/module-runtime

# Auto-generated dependencies
