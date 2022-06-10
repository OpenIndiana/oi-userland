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
# Copyright 2022 Friedrich Kink
#

BUILD_STYLE = makemaker
BUILD_BITS = 32_and_64
USE_COMMON_TEST_MASTER = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			Bit-Vector
COMPONENT_VERSION=		7.4
COMPONENT_FMRI=			library/perl-5/bit-vector
COMPONENT_SUMMARY=		Bit::Vector - Efficient bit vector, set of integers and big int math library
COMPONENT_CLASSIFICATION=	Development/Perl
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=		https://metacpan.org/dist/TimeDate
COMPONENT_ARCHIVE_HASH=		sha256:3c6daa671fecfbc35f92a9385b563d65f50dfc6bdc8b4805f9ef46c0d035a926
COMPONENT_ARCHIVE_URL=		https://cpan.metacpan.org/authors/id/S/ST/STBEY/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		Artistic
COMPONENT_LICENSE_FILE=		Artistic.txt

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_TRANSFORMS += \
        '-e "/^\#/d"' \
        '-e "/^PERL/d"' \
        '-e "/^make/d"'

PERL_REQUIRED_PACKAGES += library/perl-5/carp-clan

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
