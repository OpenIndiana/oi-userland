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

COMPONENT_NAME =		Test-Most
COMPONENT_VERSION =		0.34
COMPONENT_FMRI =		library/perl-5/test-most
COMPONENT_SUMMARY =		Test::Most - Most commonly needed test functions and features.
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Test::Most
COMPONENT_ARCHIVE_HASH =	\
	sha256:c2820c8de65f5fa59f218ac2be9be98b22cc1bb1a1f371e04375aa3b6054e244
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/O/OV/OVID/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += library/perl-5/exception-class
REQUIRED_PACKAGES += library/perl-5/test-deep
REQUIRED_PACKAGES += library/perl-5/test-differences
REQUIRED_PACKAGES += library/perl-5/test-exception
REQUIRED_PACKAGES += library/perl-5/test-warn

# Auto-generated dependencies
