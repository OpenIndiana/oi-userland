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

COMPONENT_NAME =		Package-DeprecationManager
COMPONENT_VERSION =		0.17
COMPONENT_FMRI =		library/perl-5/package-deprecationmanager
COMPONENT_SUMMARY =		Package::DeprecationManager - Manage deprecation warnings for your distribution
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Package::DeprecationManager
COMPONENT_ARCHIVE_HASH =	\
	sha256:1d743ada482b5c9871d894966e87d4c20edc96931bb949fb2638b000ddd6684b
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/D/DR/DROLSKY/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

PERL_REQUIRED_PACKAGES += library/perl-5/package-stash
PERL_REQUIRED_PACKAGES += library/perl-5/params-util
PERL_REQUIRED_PACKAGES += library/perl-5/sub-install
PERL_REQUIRED_PACKAGES += library/perl-5/sub-name
PERL_REQUIRED_PACKAGES += library/perl-5/test-fatal
PERL_REQUIRED_PACKAGES += library/perl-5/test-warnings

# Auto-generated dependencies
