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

COMPONENT_NAME =		DateTime-Format-Strptime
COMPONENT_VERSION =		1.70
COMPONENT_FMRI =		library/perl-5/datetime-format-strptime
COMPONENT_SUMMARY =		DateTime::Format::Strptime - Parse and format strp and strf time patterns
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/DateTime::Format::Strptime
COMPONENT_ARCHIVE_HASH =	\
	sha256:ceead46b714c6baea3250b987078771f1ffbe217b501d6fc91ff3c5f2afbbc67
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/D/DR/DROLSKY/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

PERL_REQUIRED_PACKAGES += library/perl-5/datetime
PERL_REQUIRED_PACKAGES += library/perl-5/datetime-locale
PERL_REQUIRED_PACKAGES += library/perl-5/datetime-timezone
PERL_REQUIRED_PACKAGES += library/perl-5/package-deprecationmanager
PERL_REQUIRED_PACKAGES += library/perl-5/params-validate
PERL_REQUIRED_PACKAGES += library/perl-5/test-fatal
PERL_REQUIRED_PACKAGES += library/perl-5/test-warnings
PERL_REQUIRED_PACKAGES += library/perl-5/try-tiny

# Auto-generated dependencies
