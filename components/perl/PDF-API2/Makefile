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
USE_COMMON_TEST_MASTER = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		PDF-API2
HUMAN_VERSION =			2.043
COMPONENT_VERSION =		2.43
COMPONENT_FMRI =		library/perl-5/pdf-api2
COMPONENT_SUMMARY =		PDF::API2 - Create, modify, and examine PDF files
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/PDF::API2
COMPONENT_ARCHIVE_HASH =	\
	sha256:6312f605172973fa4d017639c217b61b1a8d6c533237ce58d5aacecfa273f0b2
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/S/SS/SSIMMS/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		LGPLv2.1

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += library/perl-5/font-ttf
REQUIRED_PACKAGES += library/perl-5/test-exception
REQUIRED_PACKAGES += library/perl-5/test-memory-cycle

# Auto-generated dependencies
