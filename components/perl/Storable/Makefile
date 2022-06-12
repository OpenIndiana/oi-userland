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

COMPONENT_NAME=			Storable
COMPONENT_VERSION=		3.25
COMPONENT_HUMAN=		3.25
COMPONENT_FMRI=			library/perl-5/storable
COMPONENT_SUMMARY=		Storable - persistence for Perl data structures
COMPONENT_CLASSIFICATION=	Development/Perl
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_HUMAN)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=		https://metacpan.org/pod/Storable
COMPONENT_ARCHIVE_HASH=		sha256:e1e96b24a076792fde52154789fe4b76034b9ad39c8a1a819ead77d50d5f1817
COMPONENT_ARCHIVE_URL=		https://cpan.metacpan.org/authors/id/N/NW/NWCLARK/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		Artistic

include $(WS_MAKE_RULES)/common.mk

#
# delete any lines up through test_harness
# delete timings
#
COMPONENT_TEST_TRANSFORMS += \
        '-e "/^make/d"' \
        '-e "s/,  *[0-9]* wallclock.*//"'

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
