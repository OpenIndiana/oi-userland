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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
# Copyright (c) 2022 Tim Mooney.  All rights reserved
#

BUILD_STYLE = makemaker
BUILD_BITS = 32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Module-Runtime
HUMAN_VERSION =			0.016
COMPONENT_VERSION =		0.16
COMPONENT_FMRI =		library/perl-5/module-runtime
COMPONENT_SUMMARY =		Module::Runtime - runtime module handling
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Module::Runtime
COMPONENT_ARCHIVE_HASH =	\
	sha256:68302ec646833547d410be28e09676db75006f4aa58a11f3bdb44ffe99f0f024
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/Z/ZE/ZEFRAM/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

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
# delete any lines up through test_harness
# delete timings
#
COMPONENT_TEST_TRANSFORMS += \
	'-e "1,/test_harness/d"' \
	'-e "s/,  *[0-9]* wallclock.*//"'

# Auto-generated dependencies
