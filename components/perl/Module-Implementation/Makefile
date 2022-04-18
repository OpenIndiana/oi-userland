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

COMPONENT_NAME=		Module-Implementation
COMPONENT_VERSION=	0.0.9
HUMAN_VERSION=		0.09
#COMPONENT_REVISION=	1
COMPONENT_FMRI=		library/perl-5/module-implementation
COMPONENT_SUMMARY=	Module::Implementation - Loads one of several alternate underlying implementations for a module
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/Module::Implementation
COMPONENT_ARCHIVE_HASH=	\
    sha256:c15f1a12f0c2130c9efff3c2e1afe5887b08ccd033bd132186d1e7d5087fd66d
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/D/DR/DROLSKY/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	Artistic

# until all perl modules have been rebuilt with 5.34, each module sets
# this manually, before including common.mk
PERL_VERSIONS = 5.22 5.24 5.34
PERL_64_ONLY_VERSIONS = 5.24 5.34

include $(WS_MAKE_RULES)/common.mk

#
# use the results for each perl version
#
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(PERL_VERSION).master

#
# filter out all output up to and including the test_harness line
# filter out timing information and anything else that varies between builds
#
COMPONENT_TEST_TRANSFORMS += \
	'-e "1,/test_harness/d"' \
	'-e "s/,  *[0-9]* wallclock.*//"'

# Manually added dependencies
REQUIRED_PACKAGES += library/perl-5/module-runtime-522
REQUIRED_PACKAGES += library/perl-5/module-runtime-524
REQUIRED_PACKAGES += library/perl-5/module-runtime-534
REQUIRED_PACKAGES += library/perl-5/try-tiny-522
REQUIRED_PACKAGES += library/perl-5/try-tiny-524
REQUIRED_PACKAGES += library/perl-5/try-tiny-534
REQUIRED_PACKAGES += library/perl-5/test-requires-522
REQUIRED_PACKAGES += library/perl-5/test-requires-524
REQUIRED_PACKAGES += library/perl-5/test-requires-534
REQUIRED_PACKAGES += library/perl-5/test-fatal-522
REQUIRED_PACKAGES += library/perl-5/test-fatal-524
REQUIRED_PACKAGES += library/perl-5/test-fatal-534

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
