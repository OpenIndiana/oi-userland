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

COMPONENT_NAME=			Carp-Clan
COMPONENT_VERSION=		6.8
COMPONENT_HUMAN=		6.08
COMPONENT_FMRI=			library/perl-5/carp-clan
COMPONENT_SUMMARY=		Carp::Clan - Report errors from perspective of caller of a clan of modules
COMPONENT_CLASSIFICATION=	Development/Perl
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_HUMAN)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=		https://metacpan.org/pod/Carp::Clan
COMPONENT_ARCHIVE_HASH=		sha256:c75f92e34422cc5a65ab05d155842b701452434e9aefb649d6e2289c47ef6708
COMPONENT_ARCHIVE_URL=		https://cpan.metacpan.org/authors/id/E/ET/ETHER/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		Artistic
COMPONENT_LICENSE_FILE=		LICENSE

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
