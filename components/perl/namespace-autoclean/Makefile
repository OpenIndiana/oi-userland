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

COMPONENT_NAME=		namespace-autoclean
COMPONENT_VERSION=	0.29
#COMPONENT_REVISION=	1
COMPONENT_FMRI=		library/perl-5/namespace-autoclean
COMPONENT_SUMMARY=	namespace::autoclean - Keep imports out of your namespace
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/namespace::autoclean
COMPONENT_ARCHIVE_HASH=	\
    sha256:45ebd8e64a54a86f88d8e01ae55212967c8aa8fed57e814085def7608ac65804
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/E/ET/ETHER/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv1, Artistic

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
REQUIRED_PACKAGES += library/perl-5/b-hooks-endofscope-522
REQUIRED_PACKAGES += library/perl-5/b-hooks-endofscope-524
REQUIRED_PACKAGES += library/perl-5/b-hooks-endofscope-534
REQUIRED_PACKAGES += library/perl-5/sub-identify-522
REQUIRED_PACKAGES += library/perl-5/sub-identify-524
REQUIRED_PACKAGES += library/perl-5/sub-identify-534
REQUIRED_PACKAGES += library/perl-5/namespace-clean-522
REQUIRED_PACKAGES += library/perl-5/namespace-clean-524
REQUIRED_PACKAGES += library/perl-5/namespace-clean-534
REQUIRED_PACKAGES += library/perl-5/test-requires-522
REQUIRED_PACKAGES += library/perl-5/test-requires-524
REQUIRED_PACKAGES += library/perl-5/test-requires-534
REQUIRED_PACKAGES += library/perl-5/moo-522
REQUIRED_PACKAGES += library/perl-5/moo-524
REQUIRED_PACKAGES += library/perl-5/moo-534
REQUIRED_PACKAGES += library/perl-5/sub-name-522
REQUIRED_PACKAGES += library/perl-5/sub-name-524
REQUIRED_PACKAGES += library/perl-5/sub-name-534
REQUIRED_PACKAGES += library/perl-5/mouse-522
REQUIRED_PACKAGES += library/perl-5/mouse-524
REQUIRED_PACKAGES += library/perl-5/mouse-534
REQUIRED_PACKAGES += library/perl-5/test-needs-522
REQUIRED_PACKAGES += library/perl-5/test-needs-524
REQUIRED_PACKAGES += library/perl-5/test-needs-534

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
