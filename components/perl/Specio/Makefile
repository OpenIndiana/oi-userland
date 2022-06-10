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

COMPONENT_NAME =		Specio
COMPONENT_VERSION =		0.47
COMPONENT_FMRI =		library/perl-5/specio
COMPONENT_SUMMARY =		Specio - Type constraints and coercions for Perl
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Specio::Library::Builtins
COMPONENT_ARCHIVE_HASH =	\
	sha256:f41307f14444f8777e572f27eeb6a964084399e7e382c47c577827ad8a286a1c
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/D/DR/DROLSKY/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += library/perl-5/devel-stacktrace
REQUIRED_PACKAGES += library/perl-5/eval-closure
REQUIRED_PACKAGES += library/perl-5/module-runtime
REQUIRED_PACKAGES += library/perl-5/mro-compat
REQUIRED_PACKAGES += library/perl-5/role-tiny
REQUIRED_PACKAGES += library/perl-5/sub-quote
REQUIRED_PACKAGES += library/perl-5/test-fatal
REQUIRED_PACKAGES += library/perl-5/test-needs
REQUIRED_PACKAGES += library/perl-5/try-tiny
REQUIRED_PACKAGES += library/perl-5/xstring

# Auto-generated dependencies
