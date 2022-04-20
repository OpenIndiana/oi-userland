#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright 2022 Niklas Poslovski
#

BUILD_STYLE=makemaker
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Crypt-PBKDF2
COMPONENT_VERSION=	0.161520
#COMPONENT_REVISION=	1
COMPONENT_FMRI=		library/perl-5/crypt-pbkdf2
COMPONENT_SUMMARY=	Crypt::PBKDF2 - The PBKDF2 password hashing algorithm.
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/Crypt::PBKDF2
COMPONENT_ARCHIVE_HASH=	\
    sha256:97dfa79a309a086e184a4e61047f8a10ffb3db051025e7d222a25f19130ba417
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/A/AR/ARODLAND/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv1, Artistic

# until all perl modules have been rebuilt with 5.34, each module sets
# this manually, before including common.mk
PERL_VERSIONS = 5.22 5.24 5.34
PERL_64_ONLY_VERSIONS = 5.24 5.34

include $(WS_MAKE_RULES)/common.mk

#
# use the same results for comparison for all builds
#
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

#
# filter out all output up to and including the test_harness line
# filter out timing information and anything else that varies between builds
#
COMPONENT_TEST_TRANSFORMS += \
	'-e "1,/test_harness/d"' \
	'-e "s/,  *[0-9]* wallclock.*//"'

# Manually added dependencies
REQUIRED_PACKAGES += library/perl-5/digest-hmac-522
REQUIRED_PACKAGES += library/perl-5/digest-hmac-524
REQUIRED_PACKAGES += library/perl-5/digest-hmac-534
REQUIRED_PACKAGES += library/perl-5/digest-sha3-522
REQUIRED_PACKAGES += library/perl-5/digest-sha3-524
REQUIRED_PACKAGES += library/perl-5/digest-sha3-534
REQUIRED_PACKAGES += library/perl-5/module-runtime-522
REQUIRED_PACKAGES += library/perl-5/module-runtime-524
REQUIRED_PACKAGES += library/perl-5/module-runtime-534
REQUIRED_PACKAGES += library/perl-5/moo-522
REQUIRED_PACKAGES += library/perl-5/moo-524
REQUIRED_PACKAGES += library/perl-5/moo-534
REQUIRED_PACKAGES += library/perl-5/try-tiny-522
REQUIRED_PACKAGES += library/perl-5/try-tiny-524
REQUIRED_PACKAGES += library/perl-5/try-tiny-534
REQUIRED_PACKAGES += library/perl-5/type-tiny-522
REQUIRED_PACKAGES += library/perl-5/type-tiny-524
REQUIRED_PACKAGES += library/perl-5/type-tiny-534
REQUIRED_PACKAGES += library/perl-5/namespace-autoclean-522
REQUIRED_PACKAGES += library/perl-5/namespace-autoclean-524
REQUIRED_PACKAGES += library/perl-5/namespace-autoclean-534
REQUIRED_PACKAGES += library/perl-5/strictures-522
REQUIRED_PACKAGES += library/perl-5/strictures-524
REQUIRED_PACKAGES += library/perl-5/strictures-534
REQUIRED_PACKAGES += library/perl-5/test-fatal-522
REQUIRED_PACKAGES += library/perl-5/test-fatal-524
REQUIRED_PACKAGES += library/perl-5/test-fatal-534

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
