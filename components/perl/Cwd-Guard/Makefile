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

BUILD_STYLE=modulebuild
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Cwd-Guard
COMPONENT_VERSION=	0.0.5
HUMAN_VERSION=		0.05
#COMPONENT_REVISION=	1
COMPONENT_FMRI=		library/perl-5/cwd-guard
COMPONENT_SUMMARY=	Cwd::Guard - Temporary changing working directory (chdir)
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/Cwd::Guard
COMPONENT_ARCHIVE_HASH=	\
    sha256:7afc7ca2b9502e440241938ad97a3e7ebd550180ebd6142e1db394186b268e77
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/K/KA/KAZEBURO/$(COMPONENT_ARCHIVE)
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
	'-e "s/,  *[0-9]* wallclock.*//"'

# Manually added dependencies
REQUIRES_PACKAGES += library/perl-5/module-build-522
REQUIRES_PACKAGES += library/perl-5/module-build-524
REQUIRES_PACKAGES += library/perl-5/module-build-534
REQUIRES_PACKAGES += library/perl-5/test-requires-522
REQUIRES_PACKAGES += library/perl-5/test-requires-524
REQUIRES_PACKAGES += library/perl-5/test-requires-534

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
