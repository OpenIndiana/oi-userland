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

COMPONENT_NAME =		DateTime-TimeZone
HUMAN_VERSION =			2.01
COMPONENT_VERSION =		2.1
COMPONENT_FMRI =		library/perl-5/datetime-timezone
COMPONENT_SUMMARY =		DateTime::TimeZone - Time zone object base class and factory
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/DateTime::TimeZone
COMPONENT_ARCHIVE_HASH =	\
	sha256:1f673c8156fa42b2030aae46fd7e4c117f229da99dfbc7c57ef9eadd5eaa69e1
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/D/DR/DROLSKY/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

PERL_REQUIRED_PACKAGES += library/perl-5/class-singleton
PERL_REQUIRED_PACKAGES += library/perl-5/module-runtime
PERL_REQUIRED_PACKAGES += library/perl-5/params-validate
PERL_REQUIRED_PACKAGES += library/perl-5/test-fatal
PERL_REQUIRED_PACKAGES += library/perl-5/test-requires
PERL_REQUIRED_PACKAGES += library/perl-5/try-tiny

# Auto-generated dependencies
