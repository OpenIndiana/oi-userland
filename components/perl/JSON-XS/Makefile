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

COMPONENT_NAME =		JSON-XS
HUMAN_VERSION =			4.03
COMPONENT_VERSION =		4.3
COMPONENT_FMRI =		library/perl-5/json-xs
COMPONENT_SUMMARY =		JSON::XS - JSON serialising/deserialising, done correctly and fast
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/JSON::XS
COMPONENT_ARCHIVE_HASH =	\
	sha256:515536f45f2fa1a7e88c8824533758d0121d267ab9cb453a1b5887c8a56b9068
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/M/ML/MLEHMANN/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

# Disable Canary::Stability prompt
COMPONENT_CONFIGURE_ENV += PERL_CANARY_STABILITY_NOPROMPT=1

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

PERL_REQUIRED_PACKAGES += library/perl-5/canary-stability
PERL_REQUIRED_PACKAGES += library/perl-5/common-sense
PERL_REQUIRED_PACKAGES += library/perl-5/types-serialiser

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
REQUIRED_PACKAGES += system/library
