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

COMPONENT_NAME=			XSLoader
COMPONENT_VERSION=		0.24
COMPONENT_HUMAN=		0.24
COMPONENT_FMRI=			library/perl-5/xsloader
COMPONENT_SUMMARY=		XSLoader - Dynamically load C libraries into Perl code
COMPONENT_CLASSIFICATION=	Development/Perl
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_HUMAN)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=		https://metacpan.org/pod/XSLoader
COMPONENT_ARCHIVE_HASH=		sha256:e819a35a6b8e55cb61b290159861f0dc00fe9d8c4f54578eb24f612d45c8d85f
COMPONENT_ARCHIVE_URL=		https://cpan.metacpan.org/authors/id/S/SA/SAPER/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		Artistic

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_TRANSFORMS += \
        '-e "s/,  *[0-9]* wallclock.*//"' \
        '-e "/^\#/d"' \
        '-e "/^PERL/d"' \
        '-e "/^make/d"'

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
